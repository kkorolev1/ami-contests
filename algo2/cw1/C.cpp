#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    freopen("C1.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    const int MAX_VALUE = 2 * h * w;
    vector<vector<int>> adj(h, vector<int>(w));
    vector<vector<bool>> visited(h, vector<bool>(w));
    vector<vector<int>> dist(h, vector<int>(w, MAX_VALUE));

    queue<pair<int, int>> q;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> adj[i][j];
            if (adj[i][j] == 1) {
                q.push({i, j});
                visited[i][j] = true;
                dist[i][j] = 0;
            }
        }
    }

    vector<int> di = {-1, 0, 0, 1};
    vector<int> dj = {0, -1, 1, 0};

    while (!q.empty()) {
        auto& [i, j] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int ti = i + di[d];
            int tj = j + dj[d];

            if (ti >= 0 && ti < h && tj >= 0 && tj < w && !visited[ti][tj]) {
                dist[ti][tj] = dist[i][j] + 1;
                visited[ti][tj] = true;
                q.push({ti, tj});
            }

        }
    }

    int max_dist = 0;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (adj[i][j] != 1 && max_dist < dist[i][j]) {
                max_dist = dist[i][j];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (adj[i][j] != 1 && dist[i][j] == max_dist) {
                ++ans;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
