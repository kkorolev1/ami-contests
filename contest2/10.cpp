#include <vector>
#include <string>

std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> res;

    if (!str.empty()) {
        size_t from = 0;
        size_t len = 0;

        do {
            size_t to = str.find(delimiter, from);
            len = (to != std::string::npos) ? (to - from) : to;
            res.push_back(str.substr(from, len));
            from = to + 1;
        } while (len != std::string::npos);
    }

    return res;
}

#include <iostream>

int main() {
    std::string line = "13-24--08-11-2014";
    char delim = '-';
    auto ans = Split(line, delim);

    for (auto& s : ans) {
        std::cout << s << "\n";
    }

    std::cout << ans.size() << "\n";

    return 0;
}