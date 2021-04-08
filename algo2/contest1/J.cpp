#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Graph {
    Graph(int n, int m) : n_rows(n), n_cols(m), visited(n * m), source(n * m, -1), h(n * m) {}

    inline int idx(int x, int y) {
        return x * n_rows + y;
    }

    int dfs(int x, int y) {
        static vector<int> dx = {-1, 0, 0, 1};
        static vector<int> dy = {0, -1, 1, 0};

        visited[idx(x, y)] = 1;
        source[idx(x, y)] = idx(x, y);

        for (int d = 0; d < 4; ++d) {
            int tx = x + dx[d];
            int ty = y + dy[d];

            if (tx >= 0 && tx < n_rows && ty >= 0 && ty < n_cols) {
                if (h[idx(x, y)] >= h[idx(tx, ty)]) {
                    if (!visited[idx(tx, ty)])
                        source[idx(x, y)] = dfs(tx, ty);
                    else
                        source[idx(x, y)] = source[idx(tx, ty)];
                }
            }
        }

        if (source[idx(x, y)] == idx(x, y)) {
            h[idx(x, y)] = -1;
        }

        return source[idx(x, y)];
    }

    int n_rows;
    int n_cols;
    vector<int> source;
    vector<int> visited;
    vector<int> h;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    Graph g(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g.h[i * n + j];
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!g.visited[i * n + j]) {
                g.dfs(i, j);
                /*
                for (int k = 0; k < n; ++k) {
                    for (int l = 0; l < m; ++l) {
                        cout << "(" << g.source[k * n + l] / n << ", " << g.source[k * n + l] % m << ") ";
                    }
                    cout << "\n";
                }
                cout << "\n\n";*/
            }
        }
    }

    unordered_set<int> unique_sources(g.source.begin(), g.source.end());
    cout << unique_sources.size() << "\n";

    return 0;
}
