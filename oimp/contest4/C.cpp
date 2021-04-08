#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<int> xs(n);

    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        auto it = lower_bound(xs.begin(), xs.end(), x);

        if ((it == xs.end()) || (*it != x &&
            distance(xs.begin(), it) > 0 &&
            abs(*prev(it) - x) <= abs(*it - x))) {
            it = prev(it);
        }

        cout << *it << "\n";
    }


    return 0;
}
