#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

const int MAX_N = 12;
ll a[MAX_N+1][MAX_N+1];

ll s(int n, int k) {
    return k > 0 ? a[n][k] : 1;
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= MAX_N; ++i) {
        a[i][1] = i;
        for (int j = 2; j <= i; ++j) {
            a[i][j] = a[i][j-1]*(i-j+1);
        }
    }

    ll ans = 0;
    ll c[MAX_N+1] = {0};

    for (int i = 1; i <= k; ++i) {
        int x;
        cin >> x;
        ll t = 0;

        for (int j = 1; j <= x; ++j) {
            if (!c[j])
                ++t;
        }

        ans += (t-1) * s(n-i, k-i);
        c[x] = 1;
    }

    cout << ans+1 << "\n";

    return 0;
}