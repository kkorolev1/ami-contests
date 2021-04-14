#include <iostream>
#include <vector>
using namespace std;

vector<int> p;
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

    p.resize(n);
    adj.resize(n);
    visited.resize(n);

    for (int i = 0; i < n; ++i)
        cin >> p[i];

    for (int v = 0; v < n; ++v) {
        int k;
        cin >> k;

        for (int j = 0; j < k; ++j) {
            int u;
            cin >> u;
            adj[v].push_back(--u); //заполняем в другом порядке, чтобы искать конд для 1
        }
    }

    dfs(0);
    long long time = 0;

    for (int v : out) {
        time += p[v];
    }

    cout << time << " " << out.size() << "\n";

    for (int v : out) {
        cout << (v + 1) << " ";
    }


    return 0;
}
