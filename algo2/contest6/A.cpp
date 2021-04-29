#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    const int MAX_VALUE = numeric_limits<int>::max();
    vector<vector<pair<int, int>>> adj(n);
    vector<int> dist(n, MAX_VALUE);
    vector<bool> visited(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    set<pair<int, int>> s;
    dist[0] = 0;
    s.insert({dist[0], 0});

    int ans = 0;

    while (!s.empty()) {
        int v = s.begin()->second;
        s.erase(s.begin());
        visited[v] = true;
        ans += dist[v];

        for (auto& [u, w] : adj[v]) {
            if (!visited[u] && dist[u] > w) {
                s.erase({dist[u], u});
                dist[u] = w;
                s.insert({dist[u], u});
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
