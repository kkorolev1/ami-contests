#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using Point = pair<int, int>;

struct Graph {
    Graph(int n) : pts(n), visited(n) {}

    double dist(const Point& lhs, const Point& rhs) {
        return hypot(lhs.first - rhs.first, lhs.second - rhs.second);
    }

    bool dfs(int i, int freq, double power) {
        visited[i] = freq;

        for (int j = 0; j < pts.size(); ++j) {
            if (i != j && 2 * power - dist(pts[i], pts[j]) > 1e-8) {
                if (!visited[j]) {
                    if (!dfs(j, 3 - freq, power)) {
                        return false;
                    }
                } else if (visited[j] == freq) {
                    return false;
                }
            }
        }

        return true;
    }

    bool power_check(double power) {
        visited.assign(visited.size(), 0);
        return dfs(0, 1, power);
    }

    vector<int> visited;
    vector<Point> pts;
};

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Graph g(n);

    for (int i = 0; i < n; ++i) {
        cin >> g.pts[i].first >> g.pts[i].second;
    }

    double min_power = 0;
    double max_power = 1e4;
    double e = 1e-8;

    while (abs(max_power - min_power) >= e) {
        double power = (min_power + max_power) / 2;

        if (g.power_check(power)) {
            min_power = power + e;
        } else {
            max_power = power - e;
        }

    }

    cout << max_power << "\n";

    for (int freq : g.visited)
        cout << freq << " ";

    return 0;
}
