#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Point {
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    Point operator+(const Point& b) {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point& b) {
        return Point(x - b.x, y - b.y);
    }

    T dot(const Point& b) {
        return x * b.x + y * b.y;
    }

    T cross(const Point& b) {
        return x * b.y - y * b.x;
    }

    T norm_square() const {
        return x * x + y * y;
    }

    friend istream& operator>>(istream& is, Point& a) {
        is >> a.x >> a.y;
        return is;
    }

    bool operator==(const Point& b) const {
        return x == b.x && y == b.y;
    }

    bool operator!=(const Point& b) const {
        return !(*this == b);
    }
};
using Pointi = Point<int>;
using Pointd = Point<double>;

int main() {
    int n;
    cin >> n;

    vector<Pointi> points(n);

    for (auto& p : points) {
        cin >> p;
    }

    Pointi origin = points.front();
    long long ans = 0;

    for (int i = 2; i < n; ++i) {
        Pointi a = points[i - 1] - origin;
        Pointi b = points[i] - origin;
        ans += a.cross(b);
    }

    cout << fixed << setprecision(5) << (double) abs(ans) / 2;


    return 0;
}