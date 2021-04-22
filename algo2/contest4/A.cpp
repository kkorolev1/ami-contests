#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    int n, s, f;
    cin >> n >> s >> f;

    const int MAX_VALUE = 100 * n;

    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    vector<int> dist(n + 1, MAX_VALUE);

    dist[s] = 0;

    auto cmp = [&](int i, int j) {
        return dist[i] > dist[j];
    };

    priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
    q.push(s);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }

    while (!q.empty()) {
        int v = q.top();
        q.pop();

        for (int u = 1; u <= n; ++u) {
            if (v != u && g[v][u] != -1) {
                if (dist[v] + g[v][u] < dist[u]) {
                    dist[u] = dist[v] + g[v][u];
                    q.push(u);
                }
            }
        }
    }

    cout << (dist[f] != MAX_VALUE ? dist[f] : -1) << "\n";

    return 0;
}
