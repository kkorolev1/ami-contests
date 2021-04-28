#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    const int MAX_VALUE = numeric_limits<int>::max();
    vector<int> d(n, MAX_VALUE);

    d[0] = 0;

    for (int step = 0; step + 1 < n; ++step) {
        bool is_improved = false;

        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int w = ((179 * (i + 1) + 719 * (j + 1)) % 1000) - 500;
                if (d[j] > d[i] + w) {
                    is_improved = true;
                    d[j] = d[i] + w;
                }
            }
        }

        if (!is_improved)
            break;
    }

    cout << d[n - 1] << "\n";

    return 0;
}
