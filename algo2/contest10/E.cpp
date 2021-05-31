#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Graph {
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> tin, tout;
    static inline const int NUM_STEPS = 20;

    Graph(int n) : adj(n), tin(n), tout(n), up(n, vector<int>(NUM_STEPS)) {}
    int time = 0;

    void dfs(int from, int parent) {
        tin[from] = ++time;
        up[from][0] = parent;

        for (int step = 1; step < NUM_STEPS; ++step) {
            up[from][step] = up[up[from][step-1]][step-1];
        }

        for (int to : adj[from]) {
            if (to != parent) {
                dfs(to, from);
            }
        }

        tout[from] = ++time;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = up[v].size() - 1; i >= 0; --i) {
            if (!is_ancestor(up[v][i], u)) {
                v = up[v][i];
            }
        }
        return up[v][0];
    }
};

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    cin >> n;

    Graph g(n+1);

    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g.adj[a].push_back(b);
    }

    int m;
    cin >> m;

    g.dfs(0, 0);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        int lca = g.lca(x, y);
        cout << lca << "\n";
    }

}