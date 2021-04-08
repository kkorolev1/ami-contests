#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long ans = n * (n + 1) * (2 * n + 1) / 6;
    cout << ans << "\n";
    return 0;
}

