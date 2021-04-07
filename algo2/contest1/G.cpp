#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), visited(n + 1) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
    }

    int dfs(int v, int& u) {
        int d = 0;
        visited[v] = true;

        for (int neig : adj_list[v]) {
            if (!visited[neig]) {
                d = max(d, dfs(neig, u) + 1);
            }
        }

        if (d == 0) {
            u = v;
        }

        return d;
    }

    vector<bool> visited;
    vector<vector<int>> adj_list;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    int d = 0;

    for (int v = 1; v <= n; ++v) {
        if (!g.visited[v]) {
            int u = 0;
            g.dfs(v, u);
            g.visited.assign(n + 1, false);
            d = max(d, g.dfs(u, v));
        }
    }

    cout << d << "\n";

    return 0;
}
