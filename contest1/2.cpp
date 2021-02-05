#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    const char* days[] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
    cout << days[n - 1] << "\n";
    return 0;
}
