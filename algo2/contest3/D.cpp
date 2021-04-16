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

    using ll = long long;
    using Vec2 = pair<int, int>;

    struct Vec2Hash {
        size_t operator()(const Vec2& v) const {
            return hash<int>()(1000 * v.first + v.second);
        }
    };

    int num_rows, num_cols, num_flees;
    Vec2 target;
    cin >> num_rows >> num_cols >> target.first >> target.second >> num_flees;

    queue<Vec2> q;
    unordered_set<Vec2, Vec2Hash> flees;
    unordered_set<Vec2, Vec2Hash> visited;
    unordered_map<Vec2, int, Vec2Hash> dist;

    for (int i = 0; i < num_flees; ++i) {
        int x, y;
        cin >> x >> y;
        flees.emplace(x, y);
    }

    q.push(target);
    visited.insert(target);

    vector<int> dx = {-2, -2, -1, -1, 1, 1, 2, 2};
    vector<int> dy = {-1, 1, -2, 2, -2, 2, -1, 1};
    const int d_size = dx.size();

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int d = 0; d < d_size; ++d) {
            int tx = v.first + dx[d];
            int ty = v.second + dy[d];

            if (tx >= 1 && tx <= num_rows && ty >= 1 && ty <= num_cols) {
                Vec2 u{tx, ty};
                if (visited.find(u) == visited.end()) {
                    visited.insert(u);
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }

    }

    ll ans = 0;
    for (auto& f : flees) {
        if (visited.find(f) == visited.end()) {
            cout << "-1\n";
            return 0;
        }
        ans += dist[f];
    }

    cout << ans << "\n";

    return 0;
}
