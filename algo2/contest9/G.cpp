#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
const int MAX_N = 2 * 1e5;
const int INF = numeric_limits<int>::max();

struct Vertex {
    int prefix, suffix, sum, ans;

    Vertex(int value = 0) : prefix(max(0,value)), suffix(max(0,value)), sum(value), ans(max(0,value)) {}
};

Vertex t[4 * MAX_N];

int transform(int x) {
    return (abs(x)+1) % 2;
}

Vertex combine(const Vertex& l, const Vertex& r) {
    Vertex v;
    v.sum = l.sum + r.sum;
    v.prefix = max(l.prefix, l.sum + r.prefix);
    v.suffix = max(r.suffix, r.sum + l.suffix);
    v.ans = max(max(l.ans, r.ans), l.suffix + r.prefix);
    return v;
}

void build(vector<int>& a, int v, int vl, int vr) {
    if (vl == vr) {
        t[v] = Vertex(transform(a[vl]));
    } else {
        int vm = (vl + vr) / 2;
        build(a, v*2, vl, vm);
        build(a, v*2+1, vm+1, vr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

void update(int v, int vl, int vr, int index, int x) {
    if (vl == vr) {
        t[v] = Vertex(transform(x));
        return;
    }

    int tm = (vl + vr) / 2;
    if (index <= tm)
        update(v*2, vl, tm, index, x);
    else
        update(v*2+1, tm+1, vr, index, x);
    t[v] = combine(t[v*2], t[v*2+1]);
}

Vertex max_evens(int v, int vl, int vr, int ql, int qr) {
    if (ql == vl && vr == qr)
        return t[v];
    int tm = (vl + vr) / 2;
    if (qr <= tm)
        return max_evens(v*2, vl, tm, ql, qr);
    if (ql > tm)
        return max_evens(v*2+1, tm+1, vr, ql, qr);
    return combine(max_evens(v*2, vl, tm, ql, tm),
            max_evens(v*2+1, tm+1, vr, tm+1, qr));
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
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int l, r;
            cin >> l >> r;
            cout << max_evens(1, 0, n-1, l, r).ans << "\n";
        } else {
            int index, x;
            cin >> index >> x;
            update(1, 0, n-1, index, x);
        }
    }

    return 0;
}
