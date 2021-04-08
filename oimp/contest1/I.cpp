#include <iostream>
using namespace std;

bool is_palindrome(const std::string& s) {
    size_t n = s.size();
    for (size_t i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    string line, word;
    line.reserve(100);

    while (cin >> word) {
        line += word;
    }

    cout << (is_palindrome(line) ? "yes" : "no");
    return 0;
}

