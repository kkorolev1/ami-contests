#include <string>
#include <string_view>
#include <algorithm>

bool CheckPalindrome(std::string_view str) {
    size_t n = str.size();
    if (n == 0) {
        return true;
    }
    size_t l = 0, r = n - 1;
    while (l < r) {
        if (str[l++] != str[r--]) {
            return false;
        }
    }
    return true;
}

size_t CountPalindromes(std::string_view str) {
    size_t ans = 0;

    auto it = str.begin();

    do {
        auto next = std::find_if_not(it, str.end(), [](char c) { return isalpha(c); });

        if (it != next) {
            ans += CheckPalindrome(std::string_view(it, next - it));
        }

        it = std::find_if(next, str.end(), [](char c){ return isalpha(c); });
    } while (it != str.end());

    return ans;
}

#include <iostream>

using namespace std;

int main() {
    return 0;
}
