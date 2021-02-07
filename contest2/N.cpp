#include <string>

bool CheckPalindrome(const std::string& str) {
    size_t n = str.size();
    for (size_t i = 0; i < n / 2; ++i) {
        if (str[i] != str[n - i - 1]) {
            return false;
        }
    }
    return true;
}

size_t CountPalindromes(const std::string& str) {
    size_t ans = 0;

    if (!str.empty()) {
        size_t from = 0;

        while (from != std::string::npos) {
            size_t to = str.find(' ', from);
            ans += CheckPalindrome(
                    str.substr(from, (to != std::string::npos) ? (to - from) : to));
            from = (to != std::string::npos) ? (to + 1) : to;
        }
    }



    return ans;
}


#include <iostream>

using namespace std;

int main() {
    cout << CheckPalindromes("acd sgg sd abba") << "\n";
    return 0;
}
