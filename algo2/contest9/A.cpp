#include <iostream>
#include <vector>
using namespace std;

const int MODULO = 1000000007;
using ll = long long;

ll gen(ll x) {
    return (11173 * x + 1) % MODULO;
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<ll> xs(n + 1);

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        xs[i] = xs[i - 1] + x;
    }

    int q;
    ll x0;
    cin >> q >> x0;
    ll x1 = gen(x0);
    long long ans = 0;

    for (int i = 0; i < q; ++i) {
        int l = min(x0 % n, x1 % n);
        int r = max(x0 % n, x1 % n);
        ans = (ans + xs[r+1] - xs[l]) % MODULO;
        x0 = gen(x1);
        x1 = gen(x0);
    }

    cout << ans << "\n";

    return 0;
}
