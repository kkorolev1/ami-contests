#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), visited(n + 1, false) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].insert(v);
            adj_list[v].insert(u);
        }
    }

    void dfs(int v, int comp) {
        visited[v] = true;
        conn_comps[comp].push_back(v);

        for (auto& neig : adj_list[v]) {
            if (!visited[neig]) {
                dfs(neig, comp);
            }
        }
    }

    vector<bool> visited;
    vector<vector<int>> conn_comps;
    vector<unordered_set<int>> adj_list;
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }


    for (int v = 1; v <= n; ++v) {
        if (!g.visited[v]) {
            g.conn_comps.emplace_back(vector<int>{});
            g.dfs(v, g.conn_comps.size() - 1);
        }
    }

    cout << g.conn_comps.size() << "\n";

    for (auto& comp : g.conn_comps) {
        cout << comp.size() << "\n";

        for (int v : comp)
            cout << v << " ";
        cout << "\n";
    }

    return 0;
}
