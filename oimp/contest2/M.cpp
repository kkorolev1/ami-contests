#include <string>
#include <string_view>
#include <sstream>

bool NextToken(std::string_view& str, char delim, std::string_view& token) {
    if (str.empty()) {
        return false;
    }
    auto idx = str.find(delim);
    token = str.substr(0, idx);
    str = idx != std::string_view::npos ?
            str.substr(idx + 1) : std::string_view{};
    return true;
}

#include <iostream>

using namespace std;

int main() {
    string_view sv = " Hello world  and good bye";
    const char delimiter = ' ';
    string_view token;
    while (NextToken(sv, delimiter, token)) {
        // обрабатываем очередной token
        // например, печатаем его на экране:
        cout << token << "\n";
    }
    return 0;
}
