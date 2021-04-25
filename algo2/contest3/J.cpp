#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_halls, num_tunnels;
    cin >> num_halls >> num_tunnels;

    vector<vector<int>> adj(num_halls + 1);

    for (int i = 0; i < num_tunnels; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int num_robots;
    cin >> num_robots;

    using ll = long long;
    const ll INF = numeric_limits<ll>::max();

    queue<int> q;
    vector<vector<bool>> visited;
    vector<vector<ll>> d(num_halls + 1, vector<ll>(INF));
    long long ans = INF;

    for (int i = 0; i < num_robots; ++i) {
        int hall;
        cin >> hall;
        visited[hall][]
        d[start] = 0;
        q.push(hall);
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        Vertex u(num_robots);
        tick(v, u, 0, [&]() {
            if (visited.find(u) == visited.end()) {
                visited.insert(u);
                d[u] = d[v] + 1;

                if (all_of(u.begin(), u.end(), [&](int x) { return x == u.back(); })) {
                    ans = min(ans, d[u]);
                } else {
                    q.push(u);
                }
            }
        });

    }

    cout << (ans != INF ? ans : -1) << "\n";

    return 0;
}
