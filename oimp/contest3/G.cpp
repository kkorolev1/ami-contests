#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main() {
    string line;
    cin >> line;

    set<char> alphabet;

    for (char c : line)
        alphabet.insert(c);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;

        set<char> symb;

        for (char c : word) {
            symb.insert(c);
        }

        if (includes(alphabet.begin(), alphabet.end(),
                symb.begin(), symb.end())) {
            cout << word << "\n";
        }
    }

    return 0;
}
