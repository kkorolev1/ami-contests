#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    int num_cities, num_flights, num_concerts;
    cin >> num_cities >> num_flights >> num_concerts;

    const int INF = numeric_limits<int>::min();
    unordered_set<int> cycled;
    vector<vector<int>> flights(num_cities, vector<int>(num_cities));
    vector<vector<long long>> d(num_cities, vector<long long>(num_cities, INF));
    vector<vector<int>> p(num_cities, vector<int>(num_cities));

    for (int u = 0; u < num_cities; ++u) {
        for (int v = 0; v < num_cities; ++v) {
            p[u][v] = u;
        }
    }

    for (int i = 0; i < num_flights; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        d[u][v] = w;
        //p[u][v] = u;
        flights[u][v] = i;
    }

    vector<int> concerts(num_concerts);
    for (int i = 0; i < num_concerts; ++i) {
        cin >> concerts[i];
        --concerts[i];
    }

    for (int k = 0; k < num_cities; ++k) {
        for (int u = 0; u < num_cities; ++u) {
            for (int v = 0; v < num_cities; ++v) {
                if (d[u][v] < d[u][k] + d[k][v]) {
                    d[u][v] = d[u][k] + d[k][v];
                    p[u][v] = p[k][v];
                }
            }
        }
    }

    for (int u = 0; u < num_cities; ++u) {
        if (d[u][u] > 0) {
            cycled.insert(u);
        }
    }

    vector<int> ans;

    for (int i = num_concerts - 1; i > 0; --i) {
        int from = concerts[i - 1];
        int to = concerts[i];

        while (to != from) {
            if (cycled.find(to) != cycled.end()) {
                cout << "infinitely kind\n";
                return 0;
            }
            ans.push_back(flights[p[from][to]][to]);
            to = p[from][to];
        }
    }

    cout << ans.size() << "\n";

    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it+1 << " ";

    return 0;
}
