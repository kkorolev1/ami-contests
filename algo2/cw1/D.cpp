#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAX_VALUE = 1e6;
vector<vector<int>> g;
int n, k, s, f;

int min_path(int num_edges) {
    vector<int> dist(n, MAX_VALUE);
    vector<int> p(n, -1);
    dist[s] = 0;

    set<pair<int, int>> min_vs;
    min_vs.emplace(0, s);

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        if (v == f) {
            break;
        }

        for (int u = 0; u < n; ++u) {
            int w = g[v][u];
            if (u != v && w != -1 && dist[v] + w < dist[u]) {
                if (dist[u] != MAX_VALUE)
                    min_vs.erase({dist[u], u});
                dist[u] = dist[v] + w;
                p[u] = v;
                min_vs.emplace(dist[u], u);
            }
        }
    }

    int edges = 0;
    for (int v = f; v != -1; v = p[v]) {
        ++edges;
        if (num_edges < edges) {
            return 0;
        }
    }

    return dist[f];
}

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    cin >> n >> s >> f >> k;
    --s, --f;
    g.resize(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }



    for (int i = 0; i < k; ++i) {

    }

    return 0;
}