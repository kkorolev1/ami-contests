#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    struct Edge {
        int u, v, w;
    };

    const long long INF = numeric_limits<long long>::min();
    vector<long long> d(n + 1, INF);
    vector<Edge> edges(m);
    vector<int> p(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    d[1] = 0;

    for (int step = 0; step < n; ++step) {
        int impr_v = 0;

        for (auto& [u, v, w] : edges) {
            if (d[u] != INF && d[v] < d[u] + w) {
                impr_v = v;
                d[v] = d[u] + w;
                p[v] = u;
            }
        }

        if (!impr_v)
            break;
        else if (step + 1 == n) {
            int v = impr_v;
            unordered_set<int> xs;

            for (int i = 0; i < n; ++i, v = p[v]) {
                xs.insert(v);
            }

            if (xs.find(1) != xs.end() && xs.find(n) != xs.end()) {
                cout << ":)\n";
                return 0;
            }
        }
    }

    if (d[n] == INF) {
        cout << ":(\n";
    } else {
        cout << d[n] << "\n";
    }

    return 0;
}
