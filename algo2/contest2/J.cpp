#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;
set<int> ans;

void dfs(int v, int target, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];
    int children = 0;

    for (int to : adj[v]) {
        if (to == parent) {
            continue;
        } else if (!visited[to]) {
            dfs(to, target, v);
            ++children;
            up_depth[v] = min(up_depth[v], up_depth[to]);
            if (parent != -1 && up_depth[to] >= depth[v]) {
                ans.insert(v);
            }
            if (to == target) {
                break;
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

    adj.resize(n + 1);
    visited.resize(n + 1);
    depth.resize(n + 1, -1);
    up_depth.resize(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int from, to;
    cin >> from >> to;

    dfs(from, to, -1);

    cout << ans.size() << "\n";
    for (int v : ans)
        cout << v << "\n";

    return 0;
}
