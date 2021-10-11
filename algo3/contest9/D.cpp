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
};
using Pointi = Point<int>;
using Pointd = Point<double>;

int main() {
    Pointi start1, end1, start2, end2;
    cin >> start1 >> end1 >> start2 >> end2;
    Pointi vec1 = end1 - start1;
    Pointi vec2 = end2 - start2;

    if (vec1.cross(vec2) == 0 && vec1.dot(vec2) >= 0 && vec1.norm_square() <= vec2.norm_square()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}