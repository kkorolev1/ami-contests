#include <iostream>
using namespace std;

int main() {
    string number;
    getline(cin, number);
    int dx = 0;
    size_t n = number.size();

    for (size_t i = n; i > 0; --i) {
        int d = number[i - 1] - '0' + dx;
        if (i == n) {
            ++d;
        }
        number[i - 1] = (d % 10) + '0';
        dx = d / 10;
    }

    if (dx != 0) {
        cout << dx;
    }

    cout << number << "\n";

    return 0;
}

