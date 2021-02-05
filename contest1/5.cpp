#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    float ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += 1.0f / (i + 1);
    }

    for (int i = 1; i < n; i += 2) {
        ans -= 2.0f / (i + 1);
    }

    cout << ans << "\n";

    return 0;
}

