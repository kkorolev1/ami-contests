#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<vector<char>> field(h, vector<char>(w));

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> field[i][j];
        }
    }

    using Vec2 = pair<int, int>;
    Vec2 start, finish;
    cin >> start.first >> start.second >> finish.first >> finish.second;
    --start.first, --start.second, --finish.first, --finish.second;

    vector<vector<bool>> visited(h, vector<bool>(w));
    vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

    queue<Vec2> q;
    q.push(start);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == finish.first && y == finish.second) {
            cout << "found\n";
            continue;
        }

        for (int d = 0; d < 8; ++d) {
            int ty = y + dy[d];
            int tx = x + dx[d];

            if (tx >= 0 && tx < w && ty >= 0 && ty < h && field[ty][tx] != 'X' && !visited[ty][tx]) {
                visited[ty][tx] = true;


                q.push({tx, ty});
            }
        }
    }

    return 0;
}
