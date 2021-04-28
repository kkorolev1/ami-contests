#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    int s, e;
    cin >> s >> e;


    vector<vector<double>> d(n + 1, vector<double>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        int u, v;
        double p;
        cin >> u >> v >> p;
        d[u][v] = max(d[u][v], (100 - p) / 100);
        d[v][u] = max(d[v][u], (100 - p) / 100);
    }

    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (d[u][v] < d[u][k] * d[k][v]) {
                    d[u][v] = d[u][k] * d[k][v];
                }
            }
        }
    }

    double ans = 1 - d[s][e];
    cout << setprecision(3) << ans << "\n";

    return 0;
}
