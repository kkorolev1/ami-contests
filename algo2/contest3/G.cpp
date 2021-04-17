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

    int n, m;
    cin >> n >> m;

    vector<vector<int>> field(n, vector<int>(m));
    queue<State> q;
    unordered_set<State, State> visited;
    unordered_map<State, long long, State> d;

    auto not_valid_move_horizontal = [&](int x, int y) {
        return y > 0 && y+1 < m && field[x][y-1] != 1 && field[x][y+1] != 1;
    };

    auto not_valid_move_vertical = [&](int x, int y) {
        return x > 0 && x+1 < n && field[x-1][y] != 1 && field[x+1][y] != 1;
    };

    bool not_hor = true, not_ver = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
            if (field[i][j] == 2) {
                not_hor = not_valid_move_horizontal(i, j);
                not_ver = not_valid_move_vertical(i, j);

                if (!not_hor || !not_ver) {
                    State s{i, j};
                    q.push(s);
                    visited.insert(s);
                    d.emplace(s, 0);
                }
            }
        }
    }

    // нужно проверять согласуется ли предыдущий ход с текущим
    long long min_dist = numeric_limits<long long>::max();

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (Dir dir : dirs) {
            int x = v.x;
            int y = v.y;

            switch (dir) {
                case Left:
                    if (not_hor) {
                        not_hor = false;
                        continue;
                    }
                    while (y > 0 && field[x][y-1] != 1)
                        --y;
                    if (not_valid_move_vertical(x, y))
                        continue;
                    break;
                case Right:
                    if (not_hor) {
                        not_hor = false;
                        continue;
                    }
                    while (y+1 < m && field[x][y+1] != 1)
                        ++y;
                    if (not_valid_move_vertical(x, y))
                        continue;
                    break;
                case Down:
                    if (not_ver) {
                        not_ver = false;
                        continue;
                    }
                    while (x+1 < n && field[x+1][y] != 1)
                        ++x;
                    if (not_valid_move_horizontal(x, y))
                        continue;
                    break;
                case Up:
                    if (not_ver) {
                        not_ver = false;
                        continue;
                    }
                    while (x > 0 && field[x-1][y] != 1)
                        --x;
                    if (not_valid_move_horizontal(x, y))
                        continue;
                    break;
            }

            State u{x, y};

            if (visited.find(u) == visited.end()) {
                if (x == 0 && y == 0) {
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
