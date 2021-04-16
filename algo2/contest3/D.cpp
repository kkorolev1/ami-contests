#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    struct Vertex {
        int idx, x, y;

        bool operator==(const Vertex& other) const {
            return idx == other.idx && x == other.x && y == other.y;
        }

        size_t operator()(const Vertex& v) const {
            return hash<int>()(v.idx) ^ hash<int>()(1000 * v.x + v.y);
        }
    };

    int num_rows, num_cols, target_x, target_y, num_flees;
    cin >> num_rows >> num_cols >> target_x >> target_y >> num_flees;

    using ll = long long;
    queue<Vertex> q;
    unordered_set<Vertex, Vertex> visited;
    unordered_map<Vertex, ll, Vertex> dist;
    const long long MAX_VALUE = 1e9;
    vector<ll> min_dist(num_flees, MAX_VALUE);

    for (int i = 0; i < num_flees; ++i) {
        Vertex v{i};
        cin >> v.x >> v.y;
        q.push(v);
        visited.insert(v);
    }

    vector<int> dx = {-2, -2, -1, -1, 1, 1, 2, 2};
    vector<int> dy = {-1, 1, -2, 2, -1, 2, -1, 1};
    const int d_size = dx.size();

    while (!q.empty()) {
        auto& v = q.front();
        q.pop();

        if (v.x == target_x && v.y == target_y) {
            min_dist[v.idx] = min(min_dist[v.idx], dist[v]);
            continue;
        }

        for (int d = 0; d < d_size; ++d) {
            int tx = v.x + dx[d];
            int ty = v.y + dy[d];

            if (tx >= 1 && tx <= num_rows && ty >= 1 && ty <= num_cols) {
                Vertex u{v.idx, tx, ty};
                if (visited.find(u) == visited.end()) {
                    dist[u] = dist[v] + 1;
                    visited.insert(u);
                    q.push(u);
                }
            }
        }
    }

    ll ans = 0;
    for (ll d : min_dist) {
        if (d == MAX_VALUE) {
            cout << "-1\n";
            return 0;
        }
        ans += d;
    }

    cout << ans << "\n";

    return 0;
}
