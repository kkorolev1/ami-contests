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

ll evens(int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1)
            res += st[l++];
        if (r&1)
            res += st[--r];
    }
    return res;
}

void print() {
    for (int i = 0; i < 2 * n; ++i)
        cout << setw(2) << i << " ";
    cout << "\n";
    for (int x : st)
        cout << setw(2) << x << " ";
    cout << "\n";
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n0;
    cin >> n0;

    n = nearest_pow_2(n0);
    st.resize(2 * n);

    for (int i = 0; i < n0; ++i) {
        cin >> st[i+n];
        st[i+n] = (abs(st[i+n])+1)%2;
    }

    for (int i = n - 1; i > 0; --i) {
        st[i] = st[2*i] + st[2*i+1];
    }

    // print();

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int l, r;
            cin >> l >> r;
            cout << evens(l, r+1) << "\n";
        } else {
            int index, x;
            cin >> index >> x;
            modify(index, (abs(x)+1)%2);
            // print();
        }
    }

    return 0;
}
