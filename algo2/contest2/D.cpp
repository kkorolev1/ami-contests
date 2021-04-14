#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<unordered_set<int>> adj;
vector<unordered_set<int>> adj_r;
vector<int> visited;
vector<int> out;

void dfs(int v) {
    visited[v] = 1;

    for (int to : adj[v]) {
        if (!visited[to]) {
            dfs(to);
        }
    }

    out.push_back(v);
}

void dfs2(int v, int color) {
    visited[v] = color;

    for (int to : adj_r[v]) {
        if (!visited[to]) {
            dfs2(to, color);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    adj_r.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v);
        adj_r[v].insert(u);
    }

    visited.resize(n, 0);

    for (int v = 0; v < n; v++)
        if (!visited[v])
            dfs(v);

    reverse(out.begin(), out.end());
    visited.assign(n, 0);

    int color = 1;

    for (int v : out)
        if (!visited[v])
            dfs2(v, color++);

    cout << (color - 1) << "\n";

    for (int v = 0; v < n; ++v) {
        cout << visited[v] << " ";
    }

    return 0;
}
