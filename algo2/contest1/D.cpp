#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n) :
            n(n), adj_matrix(n + 1, vector<int>(n + 1)), colors(n + 1) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_matrix[u][v] = 1;
        }
    }

    bool dfs(int v, int p) {
        colors[v] = 1;

        for (int u = 1; u <= n; ++u) {
            if (adj_matrix[v][u]) {
                if (u == p)
                    continue;
                if ((colors[u] == 1) || ((colors[u] == 0) && dfs(u, v))) {
                    cycle.push_back(v);
                    return true;
                }
            }
        }

        return false;
    }

    int n;
    vector<int> cycle;
    vector<int> colors;
    vector<vector<int>> adj_matrix;
};

int main() {
    // freopen("input2.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            int has_edge;
            cin >> has_edge;
            if (has_edge)
                g.add_edge(u, v);
        }
    }

    for (int v = 1; v <= n; ++v) {
        if (!g.colors[v]) {
            if (g.dfs(v, 0)) {
                cout << "YES\n";
                cout << g.cycle.size() << "\n";

                for (int u : g.cycle) {
                    cout << u << " ";
                }

                cout << "\n";

                return 0;
            }
        }
    }

    cout << "NO\n";

    return 0;
}
