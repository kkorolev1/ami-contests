#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n) : n(n), adj_matrix(n + 1, vector<int>(n + 1, 0)), colors(n + 1, 0) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_matrix[u][v] = 1;
            adj_matrix[v][u] = 1;
        }
    }

    bool dfs(int v, int c) {
        colors[v] = 1;

        for (int u = 1; u <= n; ++u) {
            if (adj_matrix[v][u]) {
                if ((colors[v] == 1 && colors[u] == 1 && c > 2) || ((colors[u] == 0) && dfs(u, c + 1))) {
                    cycle.push_back(u);
                    return true;
                }
            }
        }

        colors[v] = 2;
        return false;
    }

    int n;
    vector<int> cycle;
    vector<int> colors;
    vector<vector<int>> adj_matrix;
};

int main() {
    // freopen("input.txt", "r", stdin);
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
            if (g.dfs(v, 1)) {
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

    cout << "NO";

    return 0;
}
