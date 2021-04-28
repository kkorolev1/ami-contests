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

    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            cout << d[u][v] << " ";
        }
        cout << "\n";
    }

    return 0;
}
