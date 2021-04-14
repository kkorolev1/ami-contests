#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> out;

void dfs(int v) {
    visited[v] = 1;

    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }

    out.push_back(v);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n);
    visited.resize(n);

    vector<int> roots;

    for (int v = 0; v < n; ++v) {
        int k;
        cin >> k;

        if (k == 0)
            roots.push_back(v);

        for (int j = 0; j < k; ++j) {
            int u;
            cin >> u;
            --u;
            adj[u].push_back(v);
        }
    }

    for (auto& lst : adj) {
        sort(lst.begin(), lst.end(), greater<int>{});
    }

    // 13808327
    // 7 8 2 1 3 5 4 6
    // 18827978
    // 2 1 3 5 4 6 7 8
    sort(roots.begin(), roots.end(), greater<int>{});

    for (int r : roots) {
        dfs(r);
    }

    reverse(out.begin(), out.end());

    /*long long ans = 0;
    long long step = 1;

    for (int i = 0; i < n; ++i) {
        ans += step * (out[i] + 1);
        step *= n;
    }

    cout << ans << "\n";*/

    for (int v : out) {
        cout << (v + 1) << " ";
    }

    return 0;
}