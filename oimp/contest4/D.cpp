#include <iostream>
#include <queue>
using namespace std;

bool greater(int x, int y) {
    if ((x == 0 && y == 9))
        return true;
    if ((x == 9 && y == 0))
        return false;
    return x > y;
}

int main() {
    // freopen("input.txt", "r", stdin);
    const int n = 5;
    queue<int> p1, p2;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        p1.push(x);
    }

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        p2.push(x);
    }

    int steps = 0;

    while (!p1.empty() && !p2.empty() && steps < 10e6) {
        int x = p1.front();
        int y = p2.front();
        p1.pop();
        p2.pop();

        if (::greater(x, y)) {
            p1.push(x);
            p1.push(y);
        } else {
            p2.push(x);
            p2.push(y);
        }

        ++steps;
    }

    if (!p1.empty() && !p2.empty()) {
        cout << "botva\n";
    } else if (p2.empty()) {
        cout << "first " << steps << "\n";
    } else {
        cout << "second " << steps << "\n";
    }


    return 0;
}
