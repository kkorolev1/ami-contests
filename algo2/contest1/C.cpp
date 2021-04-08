#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), colors(n + 1, 0) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
    }

    bool dfs(int v, int color) {
        colors[v] = color;

        for (auto& neig : adj_list[v]) {
            if (colors[neig] == colors[v] || ((colors[neig] == 0) && !dfs(neig, 3 - color))) {
                return false;
            }
        }

        return true;
    }

    vector<int> colors;
    vector<vector<int>> adj_list;
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
        if (!g.colors[v]) {
            if (!g.dfs(v, 1)) {
                cout << "NO";
                return 0;
            }
        }
    }

    cout << "YES";

    return 0;
}
