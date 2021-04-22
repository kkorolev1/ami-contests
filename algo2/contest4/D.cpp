#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    int n, k, s, f;
    cin >> n >> k;

    using ll = long long;
    const ll MAX_VALUE = 1e6 * n;

    using Edge = pair<ll, int>;
    vector<vector<Edge>> g(n + 1);
    vector<ll> dist(n + 1, MAX_VALUE);
    vector<int> from(n + 1, -1);

    for (int i = 0; i < k; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    cin >> s >> f;
    dist[s] = 0;

    set<Edge> min_vs;
    min_vs.emplace(0, s);

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        for (auto [u, w] : g[v]) {
            if (dist[v] + w < dist[u]) {
                if (dist[u] != MAX_VALUE)
                    min_vs.erase({dist[u], u});
                dist[u] = dist[v] + w;
                from[u] = v;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    if (dist[f] == MAX_VALUE) {
        cout << -1 << "\n";
        return 0;
    }

    cout << dist[f] << "\n";

    vector<int> path;

    for (int v = f; v != -1; v = from[v]) {
        path.push_back(v);
    }

    cout << path.size() << "\n";

    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << " ";

    return 0;
}
