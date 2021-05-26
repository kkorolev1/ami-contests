#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MODULO = 1000000007;
using ll = long long;

ll gen(ll x) {
    return (11173 * x + 1) % MODULO;
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    int num_levels = static_cast<int>(log2(n));

    vector<vector<ll>> sp(num_levels + 1);
    sp.front().resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> sp[0][i];
    }

    ll pow_of_two = 2;

    for (int i = 1; i <= num_levels; ++i) {
        for (int j = 0; j + pow_of_two - 1 < n; ++j) {
            sp[i].push_back(max(sp[i-1][j], sp[i-1][j + pow_of_two / 2]));
        }
        pow_of_two *= 2;
    }

    int q;
    ll x0;
    cin >> q >> x0;
    ll x1 = gen(x0);
    long long ans = 0;

    for (int i = 0; i < q; ++i) {
        int l = min(x0 % n, x1 % n);
        int r = max(x0 % n, x1 % n);

        int dist = r - l;
        pow_of_two = 1;
        int level = 0;

        while (2 * pow_of_two <= dist) {
            pow_of_two <<= 1;
            ++level;
        }

        auto s = max(sp[level][l], sp[level][r - pow_of_two + 1]);
        ans = (ans + s) % MODULO;
        x0 = gen(x1);
        x1 = gen(x0);
    }

    cout << ans << "\n";

    return 0;
}
