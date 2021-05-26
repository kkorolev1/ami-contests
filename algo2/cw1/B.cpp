#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Edge {
    int u, v, w;

    int other(int x) {
        return x == v ? u : v;
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("B1.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        auto& [u, v, w] = edges[i];
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(i);
        adj[v].emplace_back(i);
    }

    int start, coins;
    cin >> start >> coins;
    --start;

    set<pair<int, int>> s;
    const int INF = 1e9;
    vector<int> dist(n, INF);

    s.insert({0, start});
    dist[start] = 0;

    while (!s.empty()) {
        int v = s.begin()->second;
        s.erase(s.begin());

        for (auto idx : adj[v]) {
            auto& e = edges[idx];
            int u = e.other(v);

            if (dist[v] + e.w <= coins && dist[u] > dist[v] + e.w) {
                s.erase({dist[u], u});
                dist[u] = dist[v] + e.w;
                s.insert({dist[u], u});
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (dist[i] < INF) {
            ++ans;
        }
    }

    cout << ans << "\n";
    return 0;
}
