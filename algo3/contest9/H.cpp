#include <bits/stdc++.h>

using namespace std;

using Point = pair<int, int>;
int cross_product(Point& a, Point& b) {
    return a.first * b.second - a.second * b.first;
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);

    for (auto& point : points) {
        cin >> point.first >> point.second;
    }

    auto start = *min_element(points.begin(), points.end(), [](Point& a, Point& b) {
       return tie(a.second, a.first) < tie(b.second, b.first);
    });

    sort(points.begin(), points.end(), [&](Point& a, Point& b) {
        return cross_product(start, a) < cross_product(start, b);
    });

    stack<Point> s;
    s.push(start);



    return 0;
}