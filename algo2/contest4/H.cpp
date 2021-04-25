#include <iostream>
#include <vector>
#include <set>
using namespace std;

using ll = long long;
const int MAX_TIME = 1440;

struct Road {
    int a, b, time, max_w;

    int other(int v) {
        return v == a ? b : a;
    }
};

int num_nodes, num_roads;
vector<vector<Road>> g;

bool dijkstra(int num_cups) {
    vector<int> time(num_nodes + 1, MAX_TIME + 1);
    set<pair<int, int>> min_vs;
    time[1] = 0;
    min_vs.insert({0, 1});

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        if (v == num_nodes) {
            return true;
        }

        for (auto& road : g[v]) {
            int u = road.other(v);
            if (num_cups <= road.max_w && time[v] + road.time < time[u]) {
                min_vs.erase({time[u], u});
                time[u] = time[v] + road.time;

                if (time[u] > MAX_TIME)
                    return false;

                min_vs.emplace(time[u], u);
            }
        }
    }

    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    cin >> num_nodes >> num_roads;
    g.resize(num_nodes + 1);

    for (int i = 0; i < num_roads; ++i) {
        Road road{};
        cin >> road.a >> road.b >> road.time >> road.max_w;
        road.max_w = (road.max_w - 3e6) / 100;
        g[road.a].push_back(road);
        g[road.b].push_back(road);
    }

    int l = 0;
    int r = 10000000;

    while (l+1 < r) {
        int m = l + (r - l) / 2;
        if (dijkstra(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << (dijkstra(r) ? r : l) << "\n";


    return 0;
}
