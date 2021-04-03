#include <iostream>

#include <vector>
#include <string>
using namespace std;

std::string SPrintf(const std::string& format, const std::vector<std::string>& args) {
    string res;
    size_t arg_idx = 0;

    for (size_t i = 0; i < format.size(); ++i) {
        if (format[i] == '{' && i + 1 < format.size() && format[i + 1] == '}') {
            res += args[arg_idx];
            ++arg_idx;
            ++i;
        } else {
            res += format[i];
        }
    }

    return res;
}

int main() {
    cout << SPrintf("}", {"world"});
    return 0;
}
