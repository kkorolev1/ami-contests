#include <iostream>
#include <vector>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int m, n, k;
    cin >> m >> n >> k;

    const int MINE_VAL = -1;
    vector<vector<int>> field(m, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        int row, col;
        cin >> row >> col;

        if (field[--row][--col] == MINE_VAL)
            continue;

        field[row][col] = MINE_VAL;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x = col + dx;
                int y = row + dy;

                if ((dx == 0 && dy == 0) || (x < 0) || (y < 0) ||
                    (x >= n) || (y >= m) || (field[y][x] == MINE_VAL))
                    continue;

                ++field[y][x];
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (field[i][j] == MINE_VAL) {
                cout << "*";
            } else {
                cout << field[i][j];
            }
            if (j < n)
                cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
