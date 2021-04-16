#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;

    int other(int vertex) {
        return vertex == u ? v : u;
    }

    void orient(int from) {
        if (from == v)
            swap(u, v);
    }

    bool operator==(const Edge& other) const {
        return (u == other.u && v == other.v) || (u == other.v && v == other.u);
    }

    size_t operator()(const Edge& e) const {
        return hash<int>()(e.u) ^ hash<int>()(e.v);
    }
};

vector<Edge> edges;
unordered_map<Edge, int, Edge> edges_counter;
vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;

bool dfs(int v, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];

    for (int edge_idx : adj[v]) {
        auto& e = edges[edge_idx];
        int to = e.other(v);
        if (to == parent) {
            continue;
        } else if (!visited[to]) {

            if (edges_counter[e] > 1) {
                e.orient(to);
            } else {
                e.orient(v);
            }

            if (!dfs(to, v)) {
                return false;
            }

            up_depth[v] = min(up_depth[v], up_depth[to]);

            if (up_depth[to] > depth[v]) {
                return false;
            }

        } else if (visited[to] == 1) {
            e.orient(v);
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    visited[v] = 2;

    return true;
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
        Edge e{u, v};
        edges.push_back(e);
        ++edges_counter[e];
        adj[u].push_back(edges.size() - 1);
        adj[v].push_back(edges.size() - 1);
    }

    visited.resize(n, 0);
    depth.resize(n, 0);
    up_depth.resize(n, 0);


    if (!dfs(0, -1)) {
        cout << "0\n";
        return 0;
    }

    for (auto& e : edges) {
        cout << e.u + 1 << " " << e.v + 1 << "\n";
    }

    return 0;
}
