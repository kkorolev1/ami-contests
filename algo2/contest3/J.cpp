#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int m;
    cin >> m;

    using Vertex = vector<int>;

    queue<Vertex> q;
    map<Vertex, bool> visited;
    map<Vertex, int> d;

    Vertex start(m);

    for (int i = 0; i < m; ++i) {
        cin >> start[i];
    }

    visited[start] = true;
    d[start] = 0;


    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        Vertex u(m);

        for (int i = 0; i < m; ++i) {
            for (int to : adj[v[i]]) {

            }
        }
    }


    return 0;
}
