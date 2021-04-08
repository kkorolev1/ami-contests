#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Point = pair<int, int>;

double length(const Point& point) {
    return sqrt(point.first * point.first + point.second * point.second);
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end(), [](const Point& lhs, const Point& rhs){
        return length(lhs) < length(rhs);
    });

    for (auto& p : points) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}

