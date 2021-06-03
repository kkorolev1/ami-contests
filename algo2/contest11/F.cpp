#include <iostream>

using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << gcd(abs(x1-x2), abs(y1-y2))+1 << "\n";
    return 0;
}
