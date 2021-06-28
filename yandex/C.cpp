#include <iostream>
#include <vector>
using namespace std;

long long dist(int i, vector<int>& S, vector<int>& a) {
    long long ans = 0;

    for (auto& x : S) {
        ans += abs(a[i] - x);
    }

    return ans;
}

long long f(int i, int k, vector<int>& a) {
    string mask = string(a.size() - k, '0') + string(k, '1');
    long long ans = numeric_limits<long long>::max();

    do {
        vector<int> S;
        S.reserve(k);

        if (mask[i] != '1') {
            for (int j = 0; j < a.size(); ++j) {
                if (mask[j] == '1') {
                    S.push_back(a[j]);
                }
            }

            ans = min(ans, dist(i, S, a));
        }

    } while (next_permutation(mask.begin(), mask.end()));

    return ans;
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int& x : a)
        cin >> x;

    for (int i = 0; i < n; ++i) {
        cerr << i << "\n";
        cout << f(i, k, a) << " ";
    }

    return 0;
}
