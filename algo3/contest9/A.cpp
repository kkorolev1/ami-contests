#include <bits/stdc++.h>
using namespace std;

int main() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    double a = y2 - y1;
    double b = x1 - x2;
    double c = x2 * y1 - x1 * y2;
    cout << a << " " << b << " " << c << "\n";
    return 0;
}