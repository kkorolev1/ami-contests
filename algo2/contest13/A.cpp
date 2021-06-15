#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

bool is_set(int i, int bits) {
    return bits & (1 << i);
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<vector<ll>> g(n, vector<ll>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }

    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    const int NUM_SUBSETS = 1 << n;
    const ll INF = numeric_limits<ll>::max();
    vector<vector<ll>> d(NUM_SUBSETS, vector<ll>(n, INF));
    d[0][0] = 0;

    for (int subset = 0; subset < NUM_SUBSETS; ++subset) {
        for (int i = 0; i < n; ++i) {
            if (d[subset][i] != INF) {
                for (int j = 0; j < n; ++j) {
                    if (g[i][j] && !is_set(j, subset)) {
                        d[subset|(1 << j)][j] = min(d[subset|(1 << j)][j], d[subset][i] + g[i][j]);
                    }
                }
            }
        }
    }

    cout << (d[NUM_SUBSETS-1][0] != INF ? d[NUM_SUBSETS-1][0] : -1) << "\n";

    return 0;
}