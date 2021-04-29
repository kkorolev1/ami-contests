#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    const long long NO_EDGE = 100000;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1));
    vector<vector<int>> p(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> d[i][j];
            if (i == j && d[i][j] == NO_EDGE)
                d[i][j] = 0;
            p[i][j] = i;
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (d[u][k] != NO_EDGE && d[k][v] != NO_EDGE && d[u][v] > d[u][k] + d[k][v]) {
                    d[u][v] = d[u][k] + d[k][v];
                    p[u][v] = p[k][v];
                }
            }
        }
    }

    vector<int> ans;
    ans.reserve(n);

    for (int u = 1; u <= n; ++u) {
        if (d[u][u] < 0) {
            int v = u;
            unordered_set<int> xs;

            while (xs.find(v) == xs.end()) {
                ans.push_back(v);
                xs.insert(v);
                v = p[u][v];
            }

            ans.push_back(u);
            cout << "YES\n";
            cout << ans.size() << "\n";
            for (auto it = ans.rbegin(); it != ans.rend(); ++it)
                cout << *it << " ";

            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}
