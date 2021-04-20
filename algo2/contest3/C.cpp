#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    struct Vec3 {
        int x, y, z;

        size_t operator()(const Vec3& v) const {
            return hash<int>()(10000 * v.x + 100 * v.y + v.z);
        }

        bool operator==(const Vec3& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    using Block = vector<vector<char>>;
    vector<Block> cave(n, Block(n, vector<char>(n)));
    Vec3 start;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cin >> cave[i][j][k];
                if (cave[i][j][k] == 'S') {
                    start = Vec3{i, j, k};
                }
            }
        }
    }

    using ll = long long;
    queue<Vec3> q;
    unordered_set<Vec3, Vec3> visited;
    unordered_map<Vec3, ll, Vec3> dist;
    q.push(start);
    dist.emplace(start, 0);

    vector<int> dx = {-1, 1, 0, 0, 0, 0};
    vector<int> dy = {0, 0, -1, 1, 0, 0};
    vector<int> dz = {0, 0, 0, 0, -1, 1};

    ll min_dist = numeric_limits<ll>::max();

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int d = 0; d < 6; ++d) {
            int tx = v.x + dx[d];
            int ty = v.y + dy[d];
            int tz = v.z + dz[d];

            if (tx >= 0 && tx < n && ty >= 0 && ty < n && tz >= 0 && tz < n && cave[tx][ty][tz] == '.') {
                Vec3 u{tx, ty, tz};
                if (visited.find(u) == visited.end()) {
                    if (u.x == 0) {
                        min_dist = min(min_dist, dist[v] + 1);
                    } else {
                        dist[u] = dist[v] + 1;
                        visited.insert(u);
                        q.push(u);
                    }
                }
            }
        }
    }

    cout << min_dist << "\n";

    return 0;
}
