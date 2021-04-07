#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Graph {
    Graph(int n) : n(n), s(0), field(n, vector<char>(n)), adj_list(n * n), visited(n * n) {}

    void dfs(int v) {
        visited[v] = true;
        ++s;

        for (int neig : adj_list[v]) {
            if (!visited[neig]) {
                dfs(neig);
            }
        }
    }

    int n;
    vector<bool> visited;
    vector<vector<char>> field;
    vector<set<int>> adj_list;
    int s;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g.field[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g.field[i][j] == '.') {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int i_n = i + dx;
                        int j_n = j + dy;

                        if (dx == 0 && dy == 0)
                            continue;
                        if (dx == 1 && dy == 1)
                            continue;
                        if (dx == -1 && dy == -1)
                            continue;
                        if (dx == -1 && dy == 1)
                            continue;
                        if (dx == 1 && dy == -1)
                            continue;

                        if (i_n >= 0 && i_n < n && j_n >= 0 && j_n < n && g.field[i_n][j_n] == '.') {
                            int u = i * n + j;
                            int v = i_n * n + j_n;
                            g.adj_list[u].insert(v);
                            g.adj_list[v].insert(u);
                        }
                    }
                }
            }
        }
    }

    int i, j;
    cin >> i >> j;
    g.dfs((i - 1) * n + j - 1);
    cout << g.s << "\n";

    return 0;
}
