#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

using ll = long long;

struct Mark {
    ll sum = 0;
    ll n = 0;
};

int main() {
    int n;
    cin >> n;

    unordered_map<string, Mark> students;

    for (int i = 0; i < n; ++i) {
        string name;
        ll mark;
        cin >> name >> mark;
        auto& m = students[name];

        m.sum += mark;
        ++m.n;

        cout << int(floor(m.sum / m.n)) << "\n";
    }

    return 0;
}
