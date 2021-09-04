#include <iostream>
#include <vector>

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n, k, s;
    cin >> n >> k >> s;

    vector<vector<int>> subSquare(k, vector<int>(k));
    int cellsToFill = s;

    for (int i = 0; i < k; ++i) {
        if (cellsToFill < 0)
            break;
        for (int j = 0; j < k; ++j) {
            if (cellsToFill-- == 0)
                break;
            subSquare[i][j] = 1;
        }
    }

    vector<vector<int>> square(n, vector<int>(n));

    for (int i = 0, ti = 0; i < n; ++i, ti = (ti+1)%k) {
        for (int j = 0, tj = 0; j < n; ++j, tj = (tj+1)%k) {
            square[i][j] = subSquare[ti][tj];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << square[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
