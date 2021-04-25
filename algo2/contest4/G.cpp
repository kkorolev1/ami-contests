#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Route {
    int a, b, period, time;

    int other(int v) {
        return v == a ? b : a;
    }
};

using ll = long long;
using Edge = pair<ll, int>;
vector<vector<Route>> g;
int n, k;
ll max_value;

ll nearest(ll a, ll b) {
    return (a / b + (a % b != 0)) * b;
}

ll dijkstra(int from, int to, int time) {
    vector<ll> dist(n + 1, max_value);
    dist[from] = time;

    set<Edge> min_vs;
    min_vs.emplace(dist[from], from);

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        for (auto& route : g[v]) {
            int u = route.other(v);
            ll w = (ll)route.time + nearest(dist[v], route.period);
            if (w < dist[u]) {
                if (dist[u] != max_value)
                    min_vs.erase({dist[u], u});
                dist[u] = w;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    return dist[to] != max_value ? dist[to] : -1;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    cin >> n >> k;
    g.resize(n + 1);

    max_value = numeric_limits<ll>::max();

    for (int i = 0; i < k; ++i) {
        Route r{};
        cin >> r.a >> r.b >> r.period >> r.time;
        g[r.a].push_back(r);
    }

    int m;
    cin >> m;
    vector<int> control(m);

    for (int i = 0; i < m; ++i) {
        cin >> control[i];
    }

    ll time = 0;

    for (int i = 1; i < control.size(); ++i) {
        if ((time = dijkstra(control[i - 1], control[i], time)) == -1) {
            break;
        }
    }

    cout << time << "\n";

    return 0;
}
