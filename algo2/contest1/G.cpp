#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), depth(n + 1) {}

    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    void dfs(int v, int p = 0) {
        depth[v] = p != 0 ? depth[p] + 1 : 0;

        for (int neig : adj_list[v]) {
            if (neig != p) {
                dfs(neig, v);
            }
        }
    }

    vector<int> depth;
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

    g.dfs(1, 0);

    int v = max_element(g.depth.begin(), g.depth.end()) - g.depth.begin();
    g.dfs(v, 0);

    cout << *max_element(g.depth.begin(), g.depth.end()) << "\n";

    return 0;
}
