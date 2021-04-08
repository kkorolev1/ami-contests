#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n), p_old(n);

    for (int i = 0; i < n; ++i) {
        cin >> p_old[i];
    }

    for (int i = 0; i < n; ++i) {
        p[p_old[i] - 1] = i + 1;
    }

    for (int x : p) {
        cout << x << " ";
    }


    return 0;
}

