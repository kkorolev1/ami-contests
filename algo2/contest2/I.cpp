#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> depth;
vector<int> up_depth;
vector<int> subtree;
int n;
int city = -2;

int subtree_size(int from, int to, int parent) {
    if (to == parent) {
        return n - subtree[from];
    }
    return subtree[to];
}

bool check_conn_point(int v, int parent) {
    int size = subtree_size(v, adj[v].front(), parent);

    for (size_t i = 1; i < adj[v].size(); ++i) {
        if (subtree_size(v, adj[v][i], parent) != size) {
            return false;
        }
    }

    return true;
}

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
            subtree[v] += subtree[to];

            if (parent != -1 && up_depth[to] >= depth[v]) {
                if (check_conn_point(v, parent))
                    city = v;
            }
        } else {
            up_depth[v] = min(up_depth[v], depth[to]);
        }
    }

    if (parent == -1 && children > 1) {
        if (check_conn_point(v, parent))
            city = v;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    adj.resize(n);
    visited.resize(n);
    depth.resize(n);
    up_depth.resize(n);
    subtree.resize(n, 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);
    cout << city + 1 << "\n";

    return 0;
}