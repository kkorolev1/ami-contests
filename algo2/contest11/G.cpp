#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int a;
    cin >> a;

    map<int, char> powers;
    ll n = 1;

    for (int i = 2; i*i <= a; ++i) {
        if (a % i == 0) {
            n *= i;
        }

        while (a % i == 0) {
            a /= i;
            ++powers[i];
        }
    }

    if (a > 1) {
        ++powers[a];
        n *= a;
    }

    for (auto& [p, power] : powers) {
        int cur_pow = 1;

        while (int(power) > cur_pow * n) {
            ++cur_pow;
            n *= p;
        }
    }

    cout << n << "\n";

    return 0;
}
