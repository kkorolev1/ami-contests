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

    int n, m;
    cin >> n >> m;

    vector<vector<int>> field(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }

    enum Dir {
        Left = 0, Right, Up, Down
    };

    vector<Dir> dirs = {Left, Right, Up, Down};

    struct State {
        int x, y;

        bool operator==(const State& other) const {
            return x == other.x && y == other.y;
        }

        size_t operator()(const State& s) const {
            return hash<int>()(1000 * s.x + s.y);
        }
    };

    queue<State> q;
    unordered_set<State, State> visited;
    unordered_map<State, long long, State> d;

    State start{0, 0};
    q.push(start);
    visited.insert(start);
    d.emplace(start, 0);
    long long min_dist = numeric_limits<long long>::max();

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (Dir dir : dirs) {
            int x = v.x;
            int y = v.y;

            switch (dir) {
                case Left:
                    while (y > 0 && field[x][y-1] != 1 && field[x][y] != 2)
                        --y;
                    break;
                case Right:
                    while (y+1 < m && field[x][y+1] != 1 && field[x][y] != 2)
                        ++y;
                    break;
                case Down:
                    while (x+1 < n && field[x+1][y] != 1 && field[x][y] != 2)
                        ++x;
                    break;
                case Up:
                    while (x > 0 && field[x-1][y] != 1 && field[x][y] != 2)
                        --x;
                    break;
            }

            State u{x, y};

            if (visited.find(u) == visited.end()) {
                if (field[x][y] == 2) {
                    min_dist = min(min_dist, d[v] + 1);
                } else {
                    d[u] = d[v] + 1;
                    visited.insert(u);
                    q.push(u);
                }
            }
        }
    }

    cout << min_dist << "\n";

    return 0;
}