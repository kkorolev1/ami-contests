#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    using ll = long long;
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, 0));
    vector<bool> visited(n + 1);
    vector<ll> dist(n + 1);
    vector<ll> p(n + 1, -1);
    unordered_set<ll> pre_finish;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        ++adj[u][v];
        ++adj[v][u];
    }

    ll start, finish;
    cin >> start >> finish;

    queue<ll> q;
    q.push(start);
    visited[start] = true;
    dist[finish] = n + 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u = 1; u <= n; ++u) {
            if (u == v || adj[v][u] == 0)
                continue;
            if (u == finish) {
                if (dist[v] + 1 < dist[finish]) {
                    dist[finish] = dist[v] + 1;
                    pre_finish.clear();
                    pre_finish.insert(v);
                } else if (dist[v] + 1 == dist[finish]) {
                    pre_finish.insert(v);
                }
            } else if (!visited[u]) {
                dist[u] = dist[v] + 1;
                p[u] = v;
                visited[u] = true;
                q.push(u);
            }
        }
    }

    int edges = 0;

    for (int v : pre_finish) {
        edges += adj[v][finish];

        for (int u = v; p[u] != -1; u = p[u]) {
            edges += adj[p[u]][u];
            adj[p[u]][u] = 0;
            adj[u][p[u]] = 0;
        }
    }

    cout << m - edges << "\n";

    return 0;
}
