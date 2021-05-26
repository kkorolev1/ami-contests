#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long;

ll nearest_pow_2(ll x) {
    return 1 << (32 - __builtin_clz(x - 1));
}

vector<ll> st;
vector<ll> vals;
int n;

void modify(int p, int value) {
    vals[p + n] = value;
    value = (abs(value)+1)%2;

    for (st[p += n] = value; p > 1; p >>= 1)
        st[p>>1] = st[p] + st[p^1];
}

pair<ll, bool> kth(int k) {
    int p = 1;
    while (p < n) {
        if (k <= st[2*p]) {
            p = 2*p;
        } else {
            k -= st[2*p];
            p = 2*p+1;
        }
    }

    return {vals[p], st[p] == k};
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
    freopen("input.txt", "r", stdin);

    int n0;
    cin >> n0;

    n = nearest_pow_2(n0);
    st.resize(2 * n);
    vals.resize(2 * n);

    for (int i = 0; i < n0; ++i) {
        cin >> vals[i+n];
        st[i+n] = (abs(vals[i+n])+1)%2;
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
            int k;
            cin >> k;
            auto [res, has_ans] = kth(k);
            if (has_ans)
                cout << res << "\n";
            else
                cout << "NONE\n";
        } else {
            int index, x;
            cin >> index >> x;
            modify(index, x);
            // print();
        }
    }

    return 0;
}
