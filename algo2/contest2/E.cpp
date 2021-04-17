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
unordered_map<Edge, vector<int>, Edge> edges_mp;
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
            if (!dfs(to, v)) {
                return false;
            }

            up_depth[v] = min(up_depth[v], up_depth[to]);

            if (edges_mp[e].size() > 1) {
                auto [a, b] = make_pair(v, to);

                for (int edge_jdx : edges_mp[e]) {
                    edges[edge_jdx].orient(a);
                    swap(a, b);
                }

            } else {
                if (up_depth[to] > depth[v]) {
                    return false;
                }

                e.orient(v);
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

    adj.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        Edge e{u, v};
        edges.push_back(e);
        edges_mp[e].push_back(i);
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    visited.resize(n + 1);
    depth.resize(n + 1);
    up_depth.resize(n + 1);


    if (!dfs(1, -1)) {
        cout << "0\n";
        return 0;
    }

    for (auto& e : edges) {
        cout << e.u << " " << e.v << "\n";
    }

    return 0;
}
