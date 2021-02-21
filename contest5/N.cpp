#include <iostream>
#include <stdexcept>
#include <array>

class Date {
public:
    Date(int _d, int _m, int _y) {
        if (_m < 1 || _m > 12)
            throw std::invalid_argument("Month is not in [1; 12]");
        if (_d < 1 || _d > daysInMonth(_m, _y))
            throw std::invalid_argument("Day is not valid for that month and year");
        d = _d;
        m = _m;
        y = _y;
    }

    int GetDay() const { return d; }
    int GetMonth() const { return m; }
    int GetYear() const { return y; }

    Date& operator++() {
        if (d == daysInMonth(m, y)) {
            d = 1;
            if (m == 12) {
                m = 1;
                ++y;
            } else {
                ++m;
            }
        } else {
            ++d;
        }
        return *this;
    }

    Date& operator--() {
        if (d == 1) {
            if (m == 1) {
                m = 12;
                --y;
            } else {
                --m;
            }
            d = daysInMonth(m, y);
        } else {
            --d;
        }
        return *this;
    }

    Date operator+(int days) const {
        int cur_year = y;

        while (days >= 365) {
            days -= 365 + isLeapYear(cur_year++);
        }

        int cur_month = m;


    }

    int operator-(const Date& other) const {
        return dateToDays() - other.dateToDays();
    }

private:
    int dateToDays() const {
        static const int base_year = 1970;
        int days = 0;
        for (int year = base_year; year <= y; ++year)
            for (int month = 1; (year < y && month <= 12) || (month < m); ++month)
                    days += daysInMonth(month, year);
        return days + d;
    }

    static bool isLeapYear(int y) {
        return (y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0));
    }

    static int daysInMonth(int m, int y) {
        if (isLeapYear(y) && m == 2)
            return 29;
        static const std::array<int, 12> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return months[m - 1];
    }

private:
    int d;
    int m;
    int y;
};

#include <iomanip>
using namespace std;

ostream& operator<<(ostream& os, const Date& date) {
    os << setw(2) << setfill('0') << date.GetDay();
    os << "." << setw(2) << setfill('0') << date.GetMonth();
    os << "." << setw(4) << setfill('0') << date.GetYear();
    return os;
}

int main() {
    Date d(1, 1, 2021);
    Date d2(21, 2, 2021);
    cout << d2 - d << "\n";
    return 0;
}
