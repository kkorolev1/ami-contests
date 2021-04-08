#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph {
    Graph(int n, int m) : n_rows(n), n_cols(m), visited(n * m), h(n * m) {}

    inline pair<int, int> coords(int idx) {
        return make_pair(idx / n_cols, idx % n_cols);
    }

    void dfs(int v) {
        static vector<int> dx = {-1, 0, 0, 1};
        static vector<int> dy = {0, -1, 1, 0};

        visited[v] = 1;

        for (int d = 0; d < 4; ++d) {
            auto [x, y] = coords(v);
            int tx = x + dx[d];
            int ty = y + dy[d];

            if (tx >= 0 && tx < n_rows && ty >= 0 && ty < n_cols) {
                int u = tx * n_cols + ty;

                if (!visited[u] && h[v] <= h[u]) {
                    dfs(u);
                }
            }
        }
    }

    int n_rows;
    int n_cols;

    vector<int> visited;
    vector<int> h;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    Graph g(n, m);

    using Square = pair<int, int>;
    auto cmp = [](const Square& lhs, const Square& rhs) { return lhs.second > rhs.second; };
    priority_queue<Square, vector<Square>, decltype(cmp)> q(cmp);

    for (int idx = 0; idx < n * m; ++idx) {
        cin >> g.h[idx];
        q.emplace(idx, g.h[idx]);
    }

    int num_targets = 0;
    while (!q.empty()) {
        auto [v, _] = q.top();

        if (!g.visited[v]) {
            g.dfs(v);
            ++num_targets;
        }

        q.pop();
    }

    cout << num_targets << "\n";

    return 0;
}
