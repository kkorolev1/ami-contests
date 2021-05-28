#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
const int MAX_N = 2 * 1e5;
ll t[4 * MAX_N];
ll lazy[4 * MAX_N];

void build(vector<int>& a, int v, int vl, int vr) {
    if (vl == vr) {
        t[v] = a[vl];
    } else {
        int vm = (vl + vr) / 2;
        build(a, v*2, vl, vm);
        build(a, v*2+1, vm+1, vr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void push(int v, int vl, int vr) {
    if (lazy[v]) {
        t[v] += lazy[v];
        if (vl != vr) {
            lazy[2*v] = lazy[v];
            lazy[2*v+1] = lazy[v];
        }
        lazy[v] = 0;
    }
}

void update(int v, int vl, int vr, int ql, int qr, int addend) {
    if (vr < ql || qr < vl)
        return;
    if (ql <= vl && vr <= qr) {
        lazy[v] = addend;
        push(v, vl, vr);
    } else {
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(v*2, vl, vm, ql, min(qr, vm), addend);
        update(v*2+1, vm+1, vr, max(ql, vm+1), qr, addend);
        t[v] = t[v*2] + t[v*2+1];
    }
}

int sum(int v, int vl, int vr, int ql, int qr) {
    if (vr < ql || qr < vl)
        return 0;
    if (ql <= vl && vr <= qr) {
        return t[v];
    }
    push(v, vl, vr);
    int vm = (vl + vr) / 2;
    return sum(v*2, vl, vm, ql, min(qr, vm)) + sum(v*2+1, vm+1, vr, max(ql, vm+1), qr);
}


int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    build(a, 1, 0, n-1);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int cmd, l, r;
        cin >> cmd >> l >> r;

        if (cmd == 1) {
            cout << sum(1, 0, n-1, l, r) << "\n";
        } else {
            int x;
            cin >> x;
            update(1, 0, n-1, l, r, x);
        }
    }

    return 0;
}
