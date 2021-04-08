#include <iostream>
#include <array>
using namespace std;

int main() {
    int day, month, year;
    cin >> day >> month >> year;
    day += 2;

    array<int, 12> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0) {
        ++months[1];
    }

    if (day > months[month - 1]) {
        day = day % months[month - 1];
        ++month;

        if (month > 12) {
            month = 1;
            ++year;
        }
    }

    cout << day << " " << month << " " << year << "\n";

    return 0;
}