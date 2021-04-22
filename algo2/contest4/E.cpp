#include <iostream>
#include <vector>
#include <set>
using namespace std;

using ll = long long;
using Edge = pair<ll, int>;
vector<vector<Edge>> g;
int num_locs, num_roads, num_cities, capital, max_val;

ll min_dist(int to_city) {
    vector<ll> dist(num_locs + 1, max_val);

    dist[capital] = 0;

    set<Edge> min_vs;
    min_vs.emplace(0, capital);

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        if (v == to_city)
            break;

        for (auto [u, w] : g[v]) {
            if (dist[v] + w < dist[u]) {
                if (dist[u] != max_val)
                    min_vs.erase({dist[u], u});
                dist[u] = dist[v] + w;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    return dist[to_city];
}

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    cin >> num_locs >> num_roads >> num_cities >> capital;
    max_val = 100 * num_locs;

    vector<int> cities(num_cities);

    for (int i = 0; i < num_cities; ++i) {
        cin >> cities[i];
    }

    g.resize(num_locs + 1);

    for (int i = 0; i < num_roads; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<pair<ll, int>> arr_time;
    arr_time.reserve(num_cities);

    for (int city : cities) {
        arr_time.emplace_back(min_dist(city), city);
    }

    sort(arr_time.begin(), arr_time.end());

    for (auto& [time, city] : arr_time) {
        cout << city << " " << time << "\n";
    }

    return 0;
}
