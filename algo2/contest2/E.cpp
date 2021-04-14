#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, index;
};

vector<Edge> edges;
vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;

int neighbour(int edge_idx) {
    return edges[edge_idx].to;
}

bool dfs(int v, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];

    for (int e : adj[v]) {
        int to = neighbour(e);
        if (to == parent) {
            continue;
        } else if (!visited[to]) {
            if (!dfs(to, v))
                return false;
            up_depth[v] = min(up_depth[v], up_depth[to]);
            if (up_depth[to] > depth[v]) {
                cout << v << " " << to << "\n";
                return false;
            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    return true;
}

void dfs2() {

}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    visited.resize(n + 1);
    depth.resize(n + 1);
    up_depth.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(Edge{u, v, i});
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    if (!dfs(1, -1)) {
        cout << "0\n";
        return 0;
    }

    cout << "VSE NORMAS\n";


    return 0;
}
