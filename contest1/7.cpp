#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool valid_password(const string& password){
    size_t n = password.size();
    if (n < 8 || n > 14) {
        return false;
    }
    int special_chars = 0;

    for (char c: password) {
        //TODO
    }
}

int main() {
    string s;
    cin >> s;
    cout << (valid_password(s) ? "YES" : "NO") << "\n";
    return 0;
}

