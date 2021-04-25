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

    const int MAX_VALUE = 1e5 * n;

    struct Trip {
        int to, dep_time, arr_time;
    };

    vector<vector<Trip>> g(n + 1);
    vector<int> dist(n + 1, MAX_VALUE);

    for (int i = 0; i < k; ++i) {
        int from, dep_time, to, arr_time;
        cin >> from >> dep_time >> to >> arr_time;
        g[from].push_back(Trip{to, dep_time, arr_time});
    }

    dist[s] = 0;

    set<pair<int, int>> min_vs;

    for (auto& trip : g[s])
        min_vs.emplace(trip.dep_time, s);

    while (!min_vs.empty()) {
        auto [v_arr_time, v] = *min_vs.begin();
        min_vs.erase(min_vs.begin());

        for (auto& [u, dep_time, arr_time] : g[v]) {
            if (dep_time >= v_arr_time && arr_time < dist[u]) {
                if (dist[u] != MAX_VALUE)
                    min_vs.erase({dist[u], u});
                dist[u] = arr_time;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    cout << (dist[f] != MAX_VALUE ? dist[f] : -1) << "\n";

    return 0;
}
