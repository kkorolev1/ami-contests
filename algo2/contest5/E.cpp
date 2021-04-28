#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<vector<int>> d(n + 1, vector<int>(n + 1));

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            cin >> d[u][v];
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
            }
        }
    }

    int ans = numeric_limits<int>::min();

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            ans = max(ans, d[u][v]);
        }
    }

    cout << ans << "\n";
    return 0;
}
