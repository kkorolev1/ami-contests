#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    string word;
    cin >> word;
    set<char> letters(word.begin(), word.end());

    while (cin >> word) {
        set<char> tmp(word.begin(), word.end());
        set<char> res;
        set_intersection(letters.begin(), letters.end(), tmp.begin(), tmp.end(),
                inserter(res, res.begin()));
        letters = res;
    }

    for (char c : letters) {
        cout << c;
    }

    return 0;
}
