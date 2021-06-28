#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> xs(n);

    for (int& x : xs) {
        cin >> x;
    }

    if (!is_sorted(xs.begin(), xs.end())) {
        cout << "-1\n";
        return 0;
    }

    long long ans = 0;

    for (int i = 1; i < n; ++i) {
        ans += xs[i] - xs[i-1];
    }

    cout << ans << "\n";


    return 0;
}
