#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;
set<int> ans;
int t = 0;
vector<int> tin;
vector<int> tout;

void dfs(int v, int target, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    up_depth[v] = depth[v];
    int children = 0;
    tin[v] = ++t;

    for (int to : adj[v]) {
        if (to == parent) {
            continue;
        } else if (!visited[to]) {
            dfs(to, target, v);
            ++children;
            up_depth[v] = min(up_depth[v], up_depth[to]);
            if (parent != -1 && up_depth[to] >= depth[v]) {
                if (to == target || (tin[to] < tin[target] && tout[target] < tout[to])) {
                    ans.insert(v);
                }
            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    tout[v] = ++t;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    visited.resize(n + 1);
    depth.resize(n + 1);
    up_depth.resize(n + 1);
    tin.resize(n + 1, numeric_limits<int>::min());
    tout.resize(n + 1, numeric_limits<int>::max());

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
    for (int v : ans) {
        cout << v << "\n";
    }

    return 0;
}
