#include <algorithm>
#include <string>
#include <sstream>

std::string CommonSuffix(const std::string& a, const std::string& b) {
    size_t a_len = a.size();
    size_t b_len = b.size();
    std::stringstream ss;

    for (size_t i = 0, j = 0; i < a_len && j < b_len; ++i, ++j) {
        if (a[a_len - i - 1] != b[b_len - i - 1]) {
            break;
        }
        ss << a[a_len - i - 1];
    }

    auto res = ss.str();
    std::reverse(res.begin(), res.end());
    return res;
}

#include <iostream>

using namespace std;

int main() {
    cout << CommonSuffix("mycat", "cate") << "\n";
    return 0;
}