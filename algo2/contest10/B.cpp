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

int n, x, y, z;

ll gen(ll a, ll b) {
    return (x * a + y * b + z) % n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < n-1; ++i) {
        int parent;
        cin >> parent;
        g.adj[parent].push_back(i+1);
    }

    ll a1, a2;
    cin >> a1 >> a2 >> x >> y >> z;

    g.dfs(0, 0);
    int v = g.lca(a1, a2);
    ll ans = v;

    for (int i = 1; i < m; ++i) {
        a1 = gen(a1, a2);
        a2 = gen(a2, a1);
        v = g.lca((a1+v)%n, a2);
        ans += v;
    }

    cout << ans << "\n";
}