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

    struct Edge {
        int a, b;

        int other(int v) {
            return v == a ? b : a;
        }
    };

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1);
    vector<Edge> edges;

    vector<int> ldist(n + 1);
    vector<int> rdist(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back(Edge{u, v});
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    int start, finish;
    cin >> start >> finish;

    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int idx : adj[v]) {
            int u = edges[idx].other(v);
            if (!visited[u]) {
                ldist[u] = ldist[v] + 1;
                visited[u] = true;
                q.push(u);
            }
        }
    }

    visited.assign(n + 1, false);
    q.push(finish);
    visited[finish] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int idx : adj[v]) {
            int u = edges[idx].other(v);
            if (!visited[u]) {
                rdist[u] = rdist[v] + 1;
                visited[u] = true;
                q.push(u);
            }
        }
    }

    int red_edges = 0;

    for (auto& e : edges) {
        if ((ldist[e.a] + rdist[e.b] + 1 != ldist[finish]) && (ldist[e.b] + rdist[e.a] + 1 != rdist[start])) {
            ++red_edges;
        }
    }

    cout << red_edges << "\n";

    return 0;
}
