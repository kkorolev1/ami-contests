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
    vector<int> p(n, -1);
    q.push(u);
    d[u] = 0;

    while (!q.empty()) {
        int from = q.front();
        q.pop();

        if (from == v) {
            cout << d[v] << "\n";

            if (d[v] > 0) {
                vector<int> path;

                for (int x = v; x != -1; x = p[x]) {
                    path.push_back(x + 1);
                }

                reverse(path.begin(), path.end());

                for (int x : path)
                    cout << x << " ";
            }

            return 0;
        }

        for (int to = 0; to < n; ++to) {
            if (from != to && g[from][to]) {
                if (!visited[to]) {
                    visited[to] = 1;
                    q.push(to);
                }
                if (d[from] + 1 < d[to]) {
                    p[to] = from;
                    d[to] = d[from] + 1;
                }
            }
        }
    }

    cout << "-1\n";

    return 0;
}
