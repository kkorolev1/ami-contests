#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    using ll = long long;

    ll lines = 0;
    ll words = 0;
    ll letters = 0;
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        string word;

        while (ss >> word) {
            size_t symbols = count_if(word.begin(), word.end(), [](char c) { return isalpha(c); });
            letters += symbols;
            cout << word << "\n";
            ++words;
        }
        ++lines;
    }

    cout << "Input file contains:\n" << letters << " letters\n" << words << " words\n" << lines << " lines\n";

    return 0;
}

