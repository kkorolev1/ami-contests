#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Graph {
    Graph(int n) : adj_list(n + 1), colors(n + 1), time(n + 1) {}

    void add_edge(int u, int v) {
        if (u != v) {
            adj_list[u].insert(v);
        }
    }

    void dfs(int v, int c, int reach_u) {
        colors[v] = 1;
        time[v] = c;

        if (v == 1) {
            source.insert(1);
            return;
        }

        for (int neig : adj_list[v]) {
            if (colors[neig] == 1 && c > 2) {
                if (time[neig] <= time[reach_u]) {
                    source.insert(v);
                }
                //cout << "CYCLE (" << v << ", " << neig << ")\n";
            }

            if (!colors[neig]) {
                dfs(neig, c + 1, reach_u);
            }

            if (source.find(neig) != source.end()) {
                source.insert(v);
                reach_u = v;
            }
        }

        colors[v] = 2;
    }

    set<int> source;
    vector<int> time;
    vector<int> colors;
    vector<set<int>> adj_list;
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    for (int v = 1; v <= n; ++v) {
        if (!g.colors[v]){
            g.dfs(v, 1, 0);
        }
    }

    for (int v : g.source) {
        cout << v << " ";
    }

    return 0;
}
