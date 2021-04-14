#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> g(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }

    int u, v;
    cin >> u >> v;
    --u, --v;

    queue<int> q;
    vector<int> visited(n);
    vector<int> d(n, n + 1);
    q.push(u);
    d[u] = 0;

    while (!q.empty()) {
        int from = q.front();
        q.pop();

        if (from == v) {
            cout << d[v] << "\n";
            return 0;
        }

        for (int to = 0; to < n; ++to) {
            if (from != to && g[from][to]) {
                if (!visited[to]) {
                    visited[to] = 1;
                    q.push(to);
                }
                d[to] = min(d[to], d[from] + 1);
            }
        }
    }

    cout << "-1\n";

    return 0;
}
