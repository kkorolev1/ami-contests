#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int secAllowed;
    cin >> secAllowed;
    const int numCards = 31;

    vector<long long> seconds(numCards);
    cin >> seconds[0];

    for (int i = 1; i < numCards; ++i) {
        cin >> seconds[i];
        seconds[i] = max(seconds[i], 2*seconds[i-1]);
    }

    long long ans = 0;

    for (int i = numCards - 1; i >= 0; --i) {
        if (seconds[i] <= secAllowed) {
            secAllowed -= seconds[i];
            ans += 1 << i;
        }
    }

    if (secAllowed > 0)
        ++ans;

    cout << ans << "\n";

    return 0;
}