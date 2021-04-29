#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Edge {
    int v1, v2, weight;
};

struct DSU {

    DSU(int vertexCount) : parent(vertexCount) {
        for (int i = 0; i < vertexCount; ++i)
            parent[i] = i;
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void merge(int u, int v) {
        int rootOfU = find(u);
        int rootOfV = find(v);

        if (rootOfU != rootOfV) {
            if (rand() % 2) {
                parent[rootOfU] = rootOfV;
            } else {
                parent[rootOfV] = rootOfU;
            }
        }
    }

    bool connected(int u, int v) {
        return find(u) == find(v);
    }

    vector<int> parent;
};

int main() {
    freopen("input.txt", "r", stdin);
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    vector<Edge> edges(edgeCount);

    for (int i = 0; i < edgeCount; ++i) {
        auto& e = edges[i];
        cin >> e.v1 >> e.v2 >> e.weight;
        --e.v1, --e.v2;
    }

    sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs) { return lhs.weight < rhs.weight; });

    DSU dsu(vertexCount);
    int ans = 0;

    for (auto& [from, to, w] : edges) {
        if (!dsu.connected(from, to)) {
            ans += w;
            dsu.merge(from, to);
        }
    }

    cout << ans << "\n";
}
