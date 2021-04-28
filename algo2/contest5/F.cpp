#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    int num_cities, num_flights, num_concerts;
    cin >> num_cities >> num_flights >> num_concerts;

    const int INF = 1e6;
    vector<vector<long long>> d(num_cities + 1, vector<long long>(num_cities + 1, -INF));
    vector<vector<int>> p(num_cities + 1, vector<int>(num_cities + 1));
    vector<vector<int>> flights(num_cities + 1, vector<int>(num_cities + 1));

    for (int i = 0; i < num_flights; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = w;
        p[u][v] = u;
        flights[u][v] = i + 1;
    }

    vector<int> concerts(num_concerts);
    for (int i = 0; i < num_concerts; ++i) {
        cin >> concerts[i];
    }

    for (int k = 1; k <= num_cities; ++k) {
        for (int u = 1; u <= num_cities; ++u) {
            for (int v = 1; v <= num_cities; ++v) {
                if (d[u][v] < d[u][k] + d[k][v]) {
                    d[u][v] = d[u][k] + d[k][v];
                    p[u][v] = p[k][v];
                }
            }
        }
    }

    for (int u = 1; u <= num_cities; ++u) {
        if (d[u][u] > 0) {
            cout << "infinitely kind\n";
            return 0;
        }
    }

    vector<int> ans;

    for (int i = num_concerts - 1; i > 0; --i) {
        int from = concerts[i - 1];
        int to = concerts[i];

        while (to != from) {
            ans.push_back(flights[p[from][to]][to]);
            to = p[from][to];
        }
    }

    cout << ans.size() << "\n";

    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it << " ";

    return 0;
}
