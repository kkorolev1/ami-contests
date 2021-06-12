#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Graph {
    vector<vector<int>> adj;
    vector<int> tin, tout;
    vector<int> depth;
    vector<vector<int>> depthPos;
    static inline const int MAX_HEIGHT = 30;

    Graph(int n) : adj(n), tin(n), tout(n), depth(n), depthPos(MAX_HEIGHT) {}
    int time = 0;

    void dfs(int from, int parent, int d) {
        tin[from] = time++;
        depth[from] = d;

        if (d >= depthPos.size()) {
            depthPos.resize(2 * d);
        }

        depthPos[d].push_back(time);

        for (int to : adj[from]) {
            if (to != parent) {
                dfs(to, from, d + 1);
            }
        }

        tout[from] = time++;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    Graph g(n+1);

    int root = 1;
    for (int i = 1; i <= n; ++i) {
        int parent;
        cin >> parent;
        if (parent == -1)
            root = i;
        else
            g.adj[parent].push_back(i);
    }

    int m;
    cin >> m;

    g.dfs(root, root, 0);

    for (int i = 0; i < m; ++i) {
        int v, k;
        cin >> v >> k;
        ll d = g.depth[v] + k;

        if (d < g.depthPos.size()) {
            int ans = lower_bound(g.depthPos[d].begin(), g.depthPos[d].end(), g.tout[v]) -
                      upper_bound(g.depthPos[d].begin(), g.depthPos[d].end(), g.tin[v]);
            cout << ans << "\n";
        } else {
            cout << "0\n";
        }

    }
}