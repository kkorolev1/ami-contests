#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> p;

int dsuFind(int v) {
    if (p[v] == v)
        return v;
    return p[v] = dsuFind(p[v]);
}

void dsuUnion(int u, int v) {
    int uCls = dsuFind(u);
    int vCls = dsuFind(v);

    if (uCls != vCls) {
        if (rand() % 2) {
            p[vCls] = uCls;
        } else {
            p[uCls] = vCls;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    srand(0);

    int n;
    cin >> n;


    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; ++i) {
        auto& pt = points[i];
        cin >> pt.first >> pt.second;
    }

    int m;
    cin >> m;

    vector<pair<int, int>> segments(m);

    for (int i = 0; i < m; ++i) {
        auto& seg = segments[i];
        cin >> seg.first >> seg.second;
    }

    sort(segments.begin(), segments.end());

    return 0;
}
