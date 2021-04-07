#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), visited(n + 1), subtree(n + 1, 1) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
    }

    void dfs(int v, int p) {
        visited[v] = true;

        for (int neig : adj_list[v]) {
            if (!visited[neig]) {
                dfs(neig, v);
                subtree[v] += subtree[neig];
            }
        }
    }

    vector<int> subtree;
    vector<bool> visited;
    vector<vector<int>> adj_list;
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    for (int v = 1; v <= n; ++v) {
        if (!g.visited[v]) {
            g.dfs(v, 0);
        }
    }

    for (int v = 1; v <= n; ++v) {
        cout << g.subtree[v] << " ";
    }

    return 0;
}
