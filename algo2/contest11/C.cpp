#include <iostream>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    for (int i = 2; i*i <= n; ++i) {
        while (n % i == 0) {
            n /= i;
            cout << i << " ";
        }
    }

    if (n > 1)
        cout << n;
}