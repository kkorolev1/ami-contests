#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> seats(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> seats[i][j];
        }
    }

    int k;
    cin >> k;

    vector<int> sub(k, 0);

    for (int i = 0; i < n; ++i) {
        if (search(seats[i].begin(), seats[i].end(),
                sub.begin(), sub.end()) != seats[i].end()) {
            cout << (i + 1) << "\n";
            return 0;
        }
    }

    cout << "0\n";

    return 0;
}
