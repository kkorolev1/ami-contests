#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long;

ll nearest_pow_2(ll x) {
    return 1 << (32 - __builtin_clz(x - 1));
}

vector<ll> st;
int n;

void modify(int p, int value) {
    for (st[p += n] = value; p > 1; p >>= 1)
        st[p>>1] = st[p] + st[p^1];
}

ll sum(int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1)
            res += st[l++];
        if (r&1)
            res += st[--r];
    }
    return res;
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n0;
    cin >> n0;

    n = nearest_pow_2(n0);
    st.resize(2 * n);

    for (int i = 0; i < n0; ++i) {
        cin >> st[i + n];
    }

    for (int i = n - 1; i > 0; --i) {
        st[i] = st[2*i] + st[2*i+1];
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int l, r;
            cin >> l >> r;
            cout << sum(l, r+1) << "\n";
        } else {
            int index, x;
            cin >> index >> x;
            modify(index, x);
        }
    }

    return 0;
}
