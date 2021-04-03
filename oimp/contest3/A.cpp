#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;

int main() {
    // freopen("input.txt", "r", stdin);
    map<char, ll> counter;
    char c;

    while (cin >> c) {
        ++counter[c];
    }

    ll max_height = max_element(counter.begin(), counter.end(),
            [](const auto& lhs, const auto& rhs) {
                        return lhs.second < rhs.second;
                    })->second;

    for (ll i = 0; i < max_height; ++i) {
        for (auto& [_, frequency] : counter) {
            cout << ((frequency >= max_height - i) ? "#" : " ");
        }
        cout << "\n";
    }

    for (auto& [c, _] : counter) {
        cout << c;
    }

    return 0;
}