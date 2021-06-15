#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n, dist;
    cin >> n >> dist;

    vector<int> d(n);

    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    long long ans = 0;

    for (int l = 0, r = 0; l < n; ++l) {
        while (r < n && d[r] - d[l] <= dist) {
            ++r;
        }
        ans += n - r;
    }

    cout << ans << "\n";

    return 0;
}
