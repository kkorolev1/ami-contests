#include <iostream>
#include <vector>
using namespace std;

vector<bool> visited;
vector<vector<int>> adj;

void dfs(int v) {
    visited[v] = true;

    for (int to : adj[v]) {
        if (!visited[to]) {
            dfs(to);
        }
    }
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("A1.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    adj.resize(n);
    visited.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int comps = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            ++comps;
            dfs(i);
        }
    }

    cout << comps - 1 << "\n";

    return 0;
}
