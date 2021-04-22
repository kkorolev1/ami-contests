#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    int n, k, s, f;
    cin >> n >> s >> f >> k;

    using ll = long long;
    const ll MAX_VALUE = 1e6 * n;

    struct Trip {
        int to, dep_time, arr_time;
    };

    struct Edge {
        int time
    };

    using Edge = pair<ll, int>;
    vector<vector<Trip>> g(n + 1);
    vector<ll> dist(n + 1, MAX_VALUE);

    for (int i = 0; i < k; ++i) {
        int from, dep_time, to, arr_time;
        cin >> from >> dep_time >> to >> arr_time;
    }

    dist[s] = 0;

    set<Edge> min_vs;
    min_vs.emplace(0, s);

    while (!min_vs.empty()) {
        auto [v_arr_time, v] = *min_vs.begin();
        min_vs.erase(min_vs.begin());

        for (auto& [u, u_dep_time, u_arr_time] : g[v]) {
            int dt = u_dep_time - v_arr_time;
            if (dt >= 0 && dist[v] + dt < dist[u]) {
                if (dist[u] != MAX_VALUE)
                    min_vs.erase({dist[u], u});
                dist[u] = dist[v] + dt;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    cout << (dist[f] != MAX_VALUE ? dist[f] : -1) << "\n";

    return 0;
}
