#include <stdexcept>
#include <array>

using namespace std;

struct LegacyDate {
    int d, m, y;
};

class Date {
public:
    Date(int _d, int _m, int _y) {
        if (_y < 1970 || _y > 2099)
            throw std::invalid_argument("Year is not in [1970; 2099]");
        if (_m < 1 || _m > 12)
            throw std::invalid_argument("Month is not in [1; 12]");
        if (_d < 1 || _d > daysInMonth(_m, _y))
            throw std::invalid_argument("Day is not valid for that month and year");
        d = toDays(_d, _m, _y);
    }

    int GetDay() const {
        return toLegacy(d).d;
    }

    int GetMonth() const {
        return toLegacy(d).m;
    }

    int GetYear() const {
        return toLegacy(d).y;
    }

    Date operator+(int days) const {
        return Date(d + days);
    }

    Date operator-(int days) const {
        return Date(d - days);
    }

    int operator-(const Date& other) const {
        return d - other.d;
    }

    Date& operator++() {
        ++d;
        return *this;
    }

    Date& operator--() {
        --d;
        return *this;
    }

private:
    Date(int _d) : d(_d) {}

    static LegacyDate toLegacy(int days) {
        int year = 1970;

        while (daysInYear(year) <= days) {
            days -= daysInYear(year);
            ++year;
        }

        int month = 1;
        while (daysInMonth(month, year) <= days) {
            days -= daysInMonth(month, year);
            ++month;
        }

        return {days + 1, month, year};
    }

    static int toDays(int day, int month, int year) {
        int days = day;
        for (int y = 1970; y <= year; ++y) {
            for (int m = 1; (y < year && m <= 12) || m < month; ++m) {
                days += daysInMonth(m, y);
            }
        }
        return days - 1;
    }

    static bool isLeapYear(int y) {
        return (y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0));
    }

    static int daysInYear(int y) {
        return 365 + isLeapYear(y);
    }

    static int daysInMonth(int m, int y) {
        if (isLeapYear(y) && m == 2)
            return 29;
        static const std::array<int, 12> months = {31, 28,
                                                   31, 30,
                                                   31, 30,
                                                   31, 31,
                                                   30, 31,
                                                   30, 31};
        return months[m - 1];
    }

private:
    int d;
};

#include <iostream>

#include <iomanip>
using namespace std;

ostream& operator<<(ostream& os, const Date& date) {
    os << setw(2) << setfill('0') << date.GetDay();
    os << "." << setw(2) << setfill('0') << date.GetMonth();
    os << "." << setw(4) << setfill('0') << date.GetYear();
    return os;
}

int main() {
    Date d(1, 3, 2021);
    cout << d << "\n";
    return 0;
}
