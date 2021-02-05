#include <iostream>
using namespace std;

int main() {
    for (int code = 33; code <= 126; ++code) {
        cout << char(code) << " " << code << "\n";
    }
    return 0;
}

