#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using Vec2 = pair<int, int>;

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<Vec2> points(n);
    vector<int> climb1(n), climb2(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    for (int i = 0; i < n - 1; ++i) {
        climb1[i+1] = climb1[i] + (points[i+1].second > points[i].second) * abs(points[i+1].second - points[i].second);
        climb2[i+1] = climb2[i] + (points[n-i-2].second > points[n-i-1].second) * abs(points[n-i-2].second - points[n-i-1].second);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int s, f;
        cin >> s >> f;
        --s, --f;

        if (s <= f) {
            cout << climb1[f] - climb1[s] << "\n";
        } else {
            cout << climb2[n-f-1] - climb2[n-s-1] << "\n";
        }
    }

    return 0;
}
