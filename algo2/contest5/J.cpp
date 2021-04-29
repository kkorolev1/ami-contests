#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Edge {
    int u, v, w;

    int other(int x) {
        return x == u ? v : u;
    }
};

vector<bool> visited;
vector<vector<int>> adj;
vector<Edge> edges;
vector<int> in, out;
int n, m;
int t = 0;

void dfs(int v) {
    visited[v] = true;
    in[v] = ++t;

    if (v != n - 1) {
        for (int idx : adj[v]) {
            int u = edges[idx].other(v);
            if (!visited[u]) {
                dfs(u);
            }
        }
    }

    out[v] = ++t;
}

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    cin >> n >> m;

    const long long INF = numeric_limits<long long>::min();
    vector<long long> d(n, INF);
    vector<int> p(n, -1);

    adj.resize(n);
    visited.resize(n);
    in.resize(n);
    out.resize(n);
    edges.resize(m);

    for (int i = 0; i < m; ++i) {
        auto& [u, v, w] = edges[i];
        cin >> u >> v >> w;
        --u, --v;
        adj[u].push_back(i);
    }

    d[0] = 0;

    for (int step = 0; step < n; ++step) {
        int impr_v = -1;

        for (auto& [u, v, w] : edges) {
            if (d[u] != INF && d[v] < d[u] + w) {
                impr_v = v;
                d[v] = d[u] + w;
                p[v] = u;
            }
        }

        if (impr_v == -1)
            break;
        else if (step + 1 == n) {
            unordered_set<int> xs;

            while (xs.find(impr_v) == xs.end()) {
                xs.insert(impr_v);
                impr_v = p[impr_v];
            }

            dfs(0);

            if (visited[impr_v] && visited[n - 1] && in[impr_v] <= in[n - 1] && out[impr_v] >= out[n - 1]) {
                cout << ":)\n";
                return 0;
            }
        }
    }

    if (d[n - 1] == INF) {
        cout << ":(\n";
    } else {
        cout << d[n - 1] << "\n";
    }

    return 0;
}
