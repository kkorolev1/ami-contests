#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Apple {
    int x, y, z, r;
};

vector<Apple> apples;
vector<int> visited;

bool intersects(const Apple& top, const Apple& bot) {
    int dx = top.x - bot.x;
    int dy = top.y - bot.y;
    double dist = sqrt(dx * dx + dy * dy);
    return dist <= (top.r + bot.r) && top.z >= bot.z;
}


void dfs(int v) {
    visited[v] = 1;

    for (size_t u = 0; u < apples.size(); ++u) {
        if (v != u && !visited[u] && intersects(apples[v], apples[u])) {
            dfs(u);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    apples.resize(n);
    visited.resize(n);

    for (int i = 0; i < n; ++i) {
        auto& a = apples[i];
        cin >> a.x >> a.y >> a.z >> a.r;
    }

    dfs(0);

    cout << count(visited.begin(), visited.end(), 1) << "\n";

    for (int i = 0; i < n; ++i) {
        if (visited[i])
            cout << (i + 1) << " ";
    }

    return 0;
}