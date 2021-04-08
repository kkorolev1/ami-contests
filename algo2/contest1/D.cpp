#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n) : n(n), adj_matrix(n + 1, vector<int>(n + 1)), visited(n + 1), from(n + 1, -1) {}

    int dfs(int v) {
        visited[v] = 1;

        for (int u = 1; u <= n; ++u) {
            if (from[v] == u)
                continue;
            if (adj_matrix[v][u]) {
                from[u] = v;
                if (!visited[u]) {
                    int cycle_v = dfs(u);
                    if (cycle_v != -1)
                        return cycle_v;
                } else if (visited[u] == 1) {
                    return u;
                }
            }
        }

        visited[v] = 2;
        return -1;
    }

    int n;
    vector<int> from;
    vector<int> visited;
    vector<vector<int>> adj_matrix;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            cin >> g.adj_matrix[u][v];
            g.adj_matrix[v][u] = g.adj_matrix[u][v];
        }
    }

    for (int v = 1; v <= n; ++v) {
        if (!g.visited[v]) {
            int cycle_v = g.dfs(v);
            if (cycle_v != -1) {
                cout << "YES\n";

                vector<int> cycle;
                for (int u = g.from[cycle_v]; u != cycle_v; u = g.from[u]) {
                    cycle.push_back(u);
                }
                cycle.push_back(cycle_v);
                cout << cycle.size() << "\n";

                for (int x : cycle) {
                    cout << x << " ";
                }

                return 0;
            }
        }
    }

    cout << "NO\n";

    return 0;
}
