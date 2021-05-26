#include <iostream>

bool intersects(ll l1, ll r1, ll l2, ll r2) {
    return l2 <= r1 && l1 <= r2;
}

bool nested(ll lout, ll rout, ll lin, ll rin) {
    return lout <= lin && rin <= rout;
}

long long getSum(vector<ll>& st, int from, int to, int l, int r) {
    if (nested(l, r, from, to)) {
        return st[from];
    }
    ll ans = 0;
    int left_r = (from+to)/2;
    int right_l = (from+to)/2+1;

    if (intersects(from, left_r, l, r))
        ans += getSum(st, from, left_r, l, r);
    if (intersects(right_l, to, l, r))
        ans += getSum(st, right_l, to, l, r);
    return ans;
}

void modify(vector<ll>& st, vector<ll>& mod, int from, int to, int l, int r, int x) {
    if (nested(l, r, from, to)) {
        st[from] -= x;
        mod[from] = x;
        return;
    }

    int left_r = (from+to)/2;
    int right_l = (from+to)/2+1;

    if (intersects(from, left_r, l, r)) {
        modify(st, mod, from, left_r, l, r, x);
        st[from] -= x;
    }

    if (intersects(right_l, to, l, r)) {
        modify(st, mod, right_l, to, l, r, x);
        st[from] -= x;
    }
}

int main() {

    return 0;
}
