#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;

    multiset<int> window;
    vector<int> elems(n);

    for (int i = 0; i < k - 1; ++i) {
        int x;
        cin >> x;
        window.insert(x);
        elems[i] = x;
    }

    for (int i = k - 1; i < n; ++i) {
        int x;
        cin >> x;
        window.insert(x);
        elems[i] = x;

        auto mit = window.begin();
        cout << *mit << "\n";
        window.erase(window.find(elems[i - k + 1]));
    }

    return 0;
}
