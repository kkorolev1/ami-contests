#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    unordered_set<int> seen;
    int x;

    while (cin >> x) {
        if (seen.find(x) != seen.end()) {
            cout << "YES\n";
        } else {
            seen.insert(x);
            cout << "NO\n";
        }
    }

    return 0;
}
