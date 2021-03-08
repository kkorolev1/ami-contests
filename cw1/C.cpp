#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    vector<int> digits(6, 0);
    int x;
    cin >> x;
    size_t i = 5;

    while (x > 0) {
        digits[i--] = x % 10;
        x /= 10;
    }

    for (i = 0; i < digits.size(); i += 2) {
        int d = 2 * digits[i];
        if (d > 9)
            d -= 9;
        digits[i] = d;
    }

    int res = accumulate(digits.begin(), digits.end(), 0);

    if ((res % 10) == 0)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
