#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> f(n, 1);
    set<int> not_used = {1};

    for (int i = 1; i < n; ++i) {
        f[i] = f[i-1] * (i+1);
        not_used.insert(i+1);
    }

    vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
        ll acc = 0;

        if (not_used.size() == 1) {
            ans[i] = *not_used.begin();
        } else {
            for (auto it = not_used.begin(); it != not_used.end(); ++it) {
                if (k <= acc + f[n-i-2]) {
                    ans[i] = *it;
                    not_used.erase(it);
                    k -= acc;
                    break;
                }
                acc += f[n-i-2];
            }
        }
    }

    for (int x : ans)
        cout << x << " ";

    return 0;
}
