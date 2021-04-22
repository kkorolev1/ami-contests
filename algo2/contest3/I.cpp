#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    struct Vertex {
        int station, line;

        size_t operator()(const Vertex& v) const {
            return hash<int>()(100 * v.station + line);
        }

        bool operator==(const Vertex& other) const {
            return station == other.station && line == other.line;
        }
    };

    vector<vector<int>> adj(n + 1);
    unordered_map<int, vector<int>> lines;

    for (int i = 0; i < m; ++i) {
        int p;
        cin >> p;
        int x;
        cin >> x;
        lines[x].push_back(i);

        for (int j = 1; j < p; ++j) {
            int y;
            cin >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
            lines[y].push_back(i);
            x = y;
        }
    }

    int a, b;
    cin >> a >> b;

    if (a == b) {
        cout << 0 << "\n";
        return 0;
    }

    queue<Vertex> q;
    const int MAX_VALUE = numeric_limits<int>::max();
    vector<bool> visited(n + 1);
    vector<int> d(n + 1, MAX_VALUE);
    int ans = MAX_VALUE;

    for (int line : lines[a]) {
        Vertex v{a, line};
        q.push(v);
    }

    visited[a] = true;
    d[a] = 0;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int to_station : adj[v.station]) {
            if (!visited[to_station]) {
                for (int line : lines[to_station]) {
                    Vertex u{to_station, line};
                    d[to_station] = min(d[to_station], d[v.station] + (v.line != line));

                    if (to_station == b) {
                        ans = min(ans, d[to_station]);
                    } else {
                        q.push(u);
                    }
                }
                visited[to_station] = true;
            }
        }
    }

    cout << (ans != MAX_VALUE ? ans : -1) << "\n";

    return 0;
}
