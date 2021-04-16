#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<set<int>> adj(n);
    vector<int> in_deg(n);

    for (int v = 0; v < n; ++v) {
        int k;
        cin >> k;

        for (int j = 0; j < k; ++j) {
            int u;
            cin >> u;
            --u;
            adj[v].insert(u);
            ++in_deg[u];
        }
    }

    auto cmp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        return lhs.second > rhs.second;
    };
    set<pair<int, int>, decltype(cmp)> q(cmp);

    for (int v = 0; v < n; ++v)
        q.emplace(in_deg[v], v);

    vector<int> order;

    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        order.push_back(v);

        for (int to : adj[v]) {
            q.erase({in_deg[to], to});
            --in_deg[to];
            q.insert({in_deg[to], to});
        }
    }

    reverse(order.begin(), order.end());

    for (int v : order)
        cout << v + 1 << " ";

    return 0;
}