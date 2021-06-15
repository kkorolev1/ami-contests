#include <iostream>
#include <vector>
using namespace std;

struct MaxCut {
    vector<vector<int>> g;
    vector<int> cuts[2];
    vector<int> cur_cut, ans_cut;

    int num_vertices;
    int max_sum = 0;

    MaxCut(int n) : num_vertices(n), g(n, vector<int>(n)), cur_cut(n), ans_cut(n) {}

    void solve(int v, int sum) {
        static int colors[] = {1, 2};

        if (v == num_vertices) {
            if (max_sum < sum) {
                max_sum = sum;
                ans_cut = cur_cut;
            }
            return;
        }

        for (int col : colors) {
            cur_cut[v] = col;
            cuts[col-1].push_back(v);

            int next_sum = sum;
            for (int u : cuts[2-col]) {
                next_sum += g[u][v];
            }

            solve(v + 1, next_sum);
            cuts[col-1].pop_back();
        }
    }
};

int main() {
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    MaxCut cut(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cut.g[i][j];
        }
    }

    cut.solve(0, 0);

    cout << cut.max_sum << "\n";

    for (int col : cut.ans_cut) {
        cout << col << " ";
    }

    return 0;
}