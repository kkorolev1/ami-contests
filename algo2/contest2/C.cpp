#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

vector<unordered_set<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;
set<int> ans;

void dfs(int v, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];
    int children = 0;

    for (int to : adj[v]) {
        if (to == parent) {
            continue;
        } else if (!visited[to]) {
            dfs(to, v);
            ++children;
            up_depth[v] = min(up_depth[v], up_depth[to]);
            if (parent != -1 && up_depth[to] >= depth[v]) {
                ans.insert(v);
            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    if (parent == -1 && children > 1) {
        ans.insert(v);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    visited.resize(n, 0);
    depth.resize(n, 0);
    up_depth.resize(n, 0);

    for (int v = 0; v < n; v++)
        if (!visited[v])
            dfs(v, -1);

    cout << ans.size() << "\n";
    for (int v : ans)
        cout << (v + 1) << "\n";

    return 0;
}
