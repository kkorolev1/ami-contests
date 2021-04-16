#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

using Edge = pair<int, int>;
vector<vector<Edge>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;

void dfs(int v, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];

    for (auto& [to, e] : adj[v]) {
        if (to == parent) {
            continue;
        } else if (!visited[to]) {
            dfs(to, v);
            up_depth[v] = min(up_depth[v], up_depth[to]);
            if (up_depth[to] > depth[v]) {

            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (u != v) {
            adj[u].emplace_back(v, i + 1);
            adj[v].emplace_back(u, i + 1);
        }
    }

    for (auto& lst : adj) {
        sort(lst.begin(), lst.end());
    }

    visited.resize(n, 0);
    depth.resize(n, 0);
    up_depth.resize(n, 0);

    for (int v = 0; v < n; v++)
        if (!visited[v])
            dfs(v, -1);
        

    return 0;
}
