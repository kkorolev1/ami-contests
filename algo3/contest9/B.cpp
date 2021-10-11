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

    friend istream& operator>>(istream& is, Point& a) {
        is >> a.x >> a.y;
        return is;
    }
};
using Pointi = Point<int>;
using Pointd = Point<double>;

int main() {
    Pointi point, start, end;
    cin >> point >> start >> end;
    Pointi vec1 = point - start;
    Pointi vec2 = end - start;
    if (vec1.cross(vec2) == 0 && vec1.dot(vec2) >= 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}