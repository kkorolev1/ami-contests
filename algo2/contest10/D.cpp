#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

struct Graph {
    using Edge = pair<int, int>;
    vector<vector<Edge>> adj;
    vector<vector<int>> up;
    vector<vector<int>> min_w;
    vector<int> tin, tout;
    static inline const int NUM_STEPS = 20;

    Graph(int n) : adj(n), tin(n), tout(n), up(n, vector<int>(NUM_STEPS)), min_w(n, vector<int>(NUM_STEPS, INF)) {}
    int time = 0;

    void dfs(int from, int parent) {
        tin[from] = ++time;
        up[from][0] = parent;

        for (auto [to, w] : adj[from]) {
            if (to != parent) {
                min_w[to][0] = w;
                dfs(to, from);
            }
        }

        tout[from] = ++time;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    void update(int n) {
        for (int from = 1; from <= n; ++from) {
            for (int step = 1; step < NUM_STEPS; ++step) {
                up[from][step] = up[up[from][step-1]][step-1];
                min_w[from][step] = min(min_w[from][step-1], min_w[up[from][step-1]][step-1]);
            }
        }
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

    int minToLCA(int lca, int v) {
        if (lca == v)
            return INF;
        int ans = INF;
        for (int i = up[v].size() - 1; i >= 0; --i) {
            if (lca == v)
                return ans;
            if (!is_ancestor(up[v][i], lca)) {
                ans = min(ans, min_w[v][i]);
                v = up[v][i];
            }
        }
        return min(ans, min_w[v][0]);
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    Graph g(n + 1);

    for (int i = 1; i <= n - 1; ++i) {
        int parent, weight;
        cin >> parent >> weight;
        g.adj[parent].emplace_back(i+1, weight);
    }

    int root = 1;
    g.dfs(root, root);
    g.update(n);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        int lca = g.lca(x, y);
        cout << min(g.minToLCA(lca, x), g.minToLCA(lca, y)) << "\n";
    }

    return 0;
}
