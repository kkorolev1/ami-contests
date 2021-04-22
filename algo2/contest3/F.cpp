#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int p;
        cin >> p;
        vector<int> line(p);

        for (int j = 0; j < p; ++j) {
            cin >> line[j];
        }

        for (int x = 0; x + 1 < line.size(); ++x) {
            for (int y = x + 1; y < line.size(); ++y) {
                adj[line[x]].push_back(line[y]);
                adj[line[y]].push_back(line[x]);
            }
        }
    }

    int a, b;
    cin >> a >> b;

    const int MAX_VALUE = numeric_limits<int>::max();
    vector<int> d(n + 1, MAX_VALUE);
    int ans = MAX_VALUE;

    queue<int> q;
    q.push(a);
    d[a] = 0;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (d[u] == MAX_VALUE) {
                d[u] = d[v] + 1;
                if (u == b) {
                    ans = min(ans, d[u]);
                } else {
                    q.push(u);
                }
            }
        }
    }

    cout << (ans != MAX_VALUE ? ans - 1 : -1) << "\n";

    return 0;
}
