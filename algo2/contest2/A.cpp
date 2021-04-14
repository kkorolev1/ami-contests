#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> visited;
vector<int> out;
int t = 0;

bool dfs(int i) {
    visited[i] = 1;

    for (int j : adj[i]) {
        if ((!visited[j] && !dfs(j)) || visited[j] == 1) {
            return false;
        }
    }

    visited[i] = 2;
    out[t++] = i + 1;
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    visited.resize(n);
    out.resize(n);

    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        adj[--v].push_back(--u);
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (!dfs(i)) {
                cout << -1 << "\n";
                return 0;
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << out[i] << " ";
    }

    return 0;
}
