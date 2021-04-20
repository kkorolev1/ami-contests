#include <iostream>
#include <vector>
#include <queue>
#include <

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(m);

    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        g[i].resize(p);

        for (int j = 0; j < p; ++j) {
            cin >> g[i][j];
        }
    }

    int a, b;
    cin >> a >> b;

    queue<int> q;
    vector<bool> visited(n + 1);
    vector<int> d(n + 1);
    q.push(a);
    visited[a] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
    }

    cout << "-1\n";

    return 0;
}
