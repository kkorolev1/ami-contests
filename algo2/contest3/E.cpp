#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    struct Edge {
        int a, b;

        bool operator==(const Edge& other) const {
            return (a == other.a && b == other.b) || (a == other.b && b == other.a);
        }

        size_t operator()(const Edge& e) const {
            return hash<int>()(e.a) ^ hash<int>()(e.b);
        }
    };

    queue<int> q;
    vector<vector<int>> adj(n + 1);
    unordered_multiset<Edge, Edge> edges;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.emplace(Edge{u, v});
    }

    int from, to;
    cin >> from >> to;

    q.push(from);
    edges.erase({from, from});

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (edges.find({u, v}) != edges.end()) {
                edges.erase({v, u});
                q.push(u);
            }
        }
    }

    cout << edges.size() << "\n";

    return 0;
}
