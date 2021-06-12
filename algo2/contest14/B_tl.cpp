#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using Vec2 = pair<int, int>;

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<Vec2> points(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end());

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int s, f;
        cin >> s >> f;
        int ans = 0;
        --s, --f;

        if (s <= f) {
            for (int j = s; j != f; ++j) {
                if (j+1 < n && points[j+1].second > points[j].second) {
                    ans += abs(points[j+1].second - points[j].second);
                }
            }
        } else {
            for (int j = s; j != f; --j) {
                if (j >= 1 && points[j-1].second > points[j].second) {
                    ans += abs(points[j-1].second - points[j].second);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}