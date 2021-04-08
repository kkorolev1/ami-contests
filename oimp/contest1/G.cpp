#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool valid_password(const string& password) {
    size_t n = password.size();

    if (n < 8 || n > 14) {
        return false;
    }

    size_t upper = 0, lower = 0, digits = 0;

    for (char c : password) {
        if (isupper(c))
            ++upper;
        else if (islower(c))
            ++lower;
        else if (isdigit(c))
            ++digits;
    }

    return ((upper > 0) + (lower > 0) + (digits > 0) +
        (n > (upper + lower + digits))) >= 3;
}

int main() {
    string s;
    cin >> s;
    cout << (valid_password(s) ? "YES" : "NO") << "\n";
    return 0;
}
