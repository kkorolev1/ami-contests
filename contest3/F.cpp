#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Suspect {
    set<char> symb;
    string number;
    size_t index;
    size_t corresponds;
};

int main() {
    // freopen("input.txt", "r", stdin);
    int m;
    cin >> m;

    vector<set<char>> witnesses(m);

    for (int i = 0; i < m; ++i) {
        auto& w = witnesses[i];
        string line;
        cin >> line;

        for (char c : line) {
            w.insert(c);
        }
    }

    int n;
    cin >> n;

    vector<Suspect> suspects(n);

    for (int i = 0; i < n; ++i) {
        auto& s = suspects[i];
        cin >> s.number;
        s.index = i;

        for (char c : s.number) {
            s.symb.insert(c);
        }

        for (auto& w : witnesses) {
            if (includes(s.symb.begin(), s.symb.end(), w.begin(), w.end())) {
                ++s.corresponds;
            }
        }
    }

    sort(suspects.begin(), suspects.end(),
            [](const Suspect& lhs, const Suspect& rhs) {
        if (lhs.corresponds != rhs.corresponds) {
            return lhs.corresponds > rhs.corresponds;
        }
        return lhs.index < rhs.index;
    });

    auto maximum = suspects.front();
    cout << maximum.number << "\n";

    for (auto it = suspects.begin() + 1;
        it != suspects.end() && it->corresponds == maximum.corresponds;
        ++it) {
        cout << it->number << "\n";
    }

    return 0;
}
