#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Graph {
    vector<vector<int>> adj;
    vector<int> order;
    vector<int> tin, tout;
    vector<int> depth;
    static inline const int MAX_HEIGHT = 20;

    Graph(int n) : adj(n), tin(n), tout(n), depth(n){}
    int time = 0;

    void dfs(int from, int parent, int d) {
        tin[from] = time++;
        depth[from] = d;
        order.push_back(from);

        for (int to : adj[from]) {
            if (to != parent) {
                dfs(to, from, d + 1);
            }
        }

        order.push_back(from);
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

    for (int x : g.tin) {
        cout << x << " ";
    }
    cout << "\n";

    for (int x : g.tout) {
        cout << x << " ";
    }
    cout << "\n";

    for (int x : g.order) {
        cout << x << " ";
    }
    cout << "\n";

    for (int x : g.depth) {
        cout << x << " ";
    }
    cout << "\n";

    for (int i = 0; i < m; ++i) {
        int v, k;
        cin >> v >> k;
        ll d = g.depth[v] + k;

        int counter = 0;
        for (int from = g.tin[v]; from != g.tout[v]; ++from) {
            if (g.depth[g.tin[from]] == d)
                ++counter;
        }
        cout << counter << "\n";
    }
}