#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].insert(v);
            adj_list[v].insert(u);
        }
    }

    void dfs(int v) {
        visited.insert(v);

        for (auto& neig : adj_list[v]) {
            if (visited.find(neig) == visited.end()) {
                dfs(neig);
            }
        }
    }

    set<int> visited;
    vector<set<int>> adj_list;
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

    g.dfs(1);

    cout << g.visited.size() << "\n";

    for (int v : g.visited) {
        cout << v << " ";
    }

    return 0;
}
