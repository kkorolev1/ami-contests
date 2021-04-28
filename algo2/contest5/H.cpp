#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    struct Trip {
        int from, dep, to, arr;
    };

    int n;
    cin >> n;

    int a, b;
    cin >> a >> b;

    int k;
    cin >> k;

    const int MAX_VALUE = numeric_limits<int>::max();
    vector<long long> d(n + 1, MAX_VALUE);
    vector<Trip> trips(k);

    for (int i = 0; i < k; ++i) {
        auto& t = trips[i];
        cin >> t.from >> t.dep >> t.to >> t.arr;
    }

    d[a] = 0;

    for (int step = 0; step < n; ++step) {
        bool impr = false;

        for (auto& [from, dep, to, arr] : trips) {
            if (d[from] >= dep && d[to] > arr) {
                d[to] = arr;
                impr = true;
            }
        }

        if (!impr)
            break;
    }

    cout << d[b] << "\n";

    return 0;
}
