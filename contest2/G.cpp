#include <iostream>
#include <vector>

using namespace std;

bool is_assoc(const vector<vector<int>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (matrix[matrix[i][j]][k] != matrix[i][matrix[j][k]]) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << (is_assoc(matrix, n) ? "YES" : "NO") << "\n";

    return 0;
}