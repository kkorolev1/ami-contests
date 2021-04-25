#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Route {
    int a, b, period, time;

    int other(int v) {
        return v == a ? b : a;
    }
};

using ll = long long;
using Edge = pair<ll, int>;
vector<vector<Route>> g;
vector<string_view> files;
unordered_map<string_view, vector<int>> substrs;
int n, k;
ll max_value;

void dijkstra(int from, int to) {
    vector<ll> dist(n + 1, max_value);
    dist[from] = 0;

    set<Edge> min_vs;
    min_vs.emplace(dist[from], from);

    while (!min_vs.empty()) {
        int v = min_vs.begin()->second;
        min_vs.erase(min_vs.begin());

        int u_prev = (v - 1) % files.size();
        int u_next = (v + 1) % files.size();

        for (size_t j = 0; j < files[to].size(); ++j) {
            auto file_prefix = files[to].substr(0, j + 1);
            auto& file_idxs = substrs[file_prefix];
            auto it = find(file_idxs.begin(), file_idxs.end(), v);

        }
    }

}

int main() {
    freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    ios::ios_base::sync_with_stdio(false);

    cin >> n;
    files.reserve(n);

    for (int i = 0; i < n; ++i) {
        string file;
        cin >> file;
        files.emplace_back(file);

        for (size_t j = 0; j < files[i].size(); ++j) {
            substrs[files[i].substr(0, j + 1)].push_back(i);
        }
    }

    cin >> k;

    int from = 0;

    for (int i = 0; i < k; ++i) {
        int to;
        cin >> to;
        --to;
        //dijkstra(from, to);
        from = to;
    }

    return 0;
}
