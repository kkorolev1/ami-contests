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
    Pointi start1, end1, start2, end2;
    cin >> start1 >> end1 >> start2 >> end2;
    Pointi norm1{end1.y - start1.y, start1.x - end1.x};
    Pointi norm2{end2.y - start2.y, start2.x - end2.x};
    int c1 = end1.x * start1.y - start1.x * end1.y;
    int c2 = end2.x * start2.y - start2.x * end2.y;

    if (norm1.cross(norm2) == 0) {
        if (norm1.y * c2 == norm2.y * c1 && norm1.x * c2 == norm2.x * c1) {
            cout << 2;
        } else {
            cout << 0;
        }
    } else {
        double den = norm1.cross(norm2);
        Pointi a1{-c1, norm1.y};
        Pointi a2{-c2, norm2.y};
        Pointi b1{norm1.x, -c1};
        Pointi b2{norm2.x, -c2};
        Pointd ans{a1.cross(a2) / den + 0.0, b1.cross(b2) / den + 0.0};
        cout << 1 << " ";
        cout << fixed << setprecision(2) << ans.x << " " << ans.y;
    }
    return 0;
}