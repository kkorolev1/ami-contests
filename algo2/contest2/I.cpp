#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;
vector<int> subtree;
unordered_set<int> points;

bool check_conn_point(int v) {
    int size = subtree[adj[v].front()];

    for (size_t i = 1; i < adj[v].size(); ++i) {
        if (subtree[adj[v][i]] != size) {
            return false;
        }
    }

    return true;
}

void dfs(int v, int parent) {
    visited[v] = 1;
    depth[v] = (parent == -1 ? 0 : depth[parent] + 1);
    // cout << (v + 1) << " " << depth[v] << "\n";
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
                cout << (v + 1) << ": ";

                for (int x : adj[v]) {
                    int s = depth[v] - depth[x];
                    cout << "(" << (x + 1) << " " << s << ") ";
                }
                cout << "\n";
            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    if (parent == -1 && children > 1) {

    }
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.resize(n);
    visited.resize(n);
    depth.resize(n, 0);
    up_depth.resize(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);

    cout << "-1\n";

    return 0;
}