#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    int s, e;
    cin >> s >> e;
    --s, --e;

    vector<vector<double>> d(n, vector<double>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v;
        double p;
        cin >> u >> v >> p;
        --u, --v;
        d[u][v] = 1 - p / 100.0;
        d[v][u] = 1 - p / 100.0;
    }

    for (int k = 0; k < n; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                d[u][v] = max(d[u][v], d[u][k] * d[k][v]);
            }
        }
    }

    cout << 1 - d[s][e] << "\n";

    return 0;
}