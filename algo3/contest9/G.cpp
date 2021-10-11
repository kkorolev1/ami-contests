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
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    Pointi point;
    cin >> point;

    vector<Pointi> points(n);

    for (auto& p : points) {
        cin >> p;
    }

    double angle = 0;
    int zeros = 0;

    for (int i = 0; i < n; ++i) {
        Pointi a = points[i] - point;
        Pointi b = points[(i + 1) % points.size()] - point;
        int sq_1 = a.norm_square();
        int sq_2 = b.norm_square();

        if (sq_1 && sq_2) {
            angle += acos((double) a.dot(b) / sqrt(sq_1) / sqrt(sq_2));
        } else {
            ++zeros;
        }
    }

    double epsilon = 1e-6;

    if (zeros >= 2 || abs(angle - 2 * M_PI) < epsilon || abs(angle + 2 * M_PI) < epsilon) {
        cout << "YES";
    } else {
        cout << "NO";
    }


    return 0;
}