#include <stdexcept>
#include <array>

using namespace std;

struct LegacyDate {
    int d, y, m;
};

class Date {
public:

    int DaysInYear(int year) const {
        return 365 + IsLeap(year);
    }

    Date(int _d, int _m, int _y) {
        if (_y < 1970 || _y > 2099)
            throw std::invalid_argument("Year is not in [1970; 2099]");
        if (_m < 1 || _m > 12)
            throw std::invalid_argument("Month is not in [1; 12]");
        if (_d < 1 || _d > daysInMonth(_m, _y))
            throw std::invalid_argument("Day is not valid for that month and year");
        d = to_days(_d, _m, _y);
    }

    Date(int d) {

    }

    int GetDay() const {
        auto [d, _, _] = to_day_month_year(d);
        return day;
    }

    int GetMonth() const {
        auto [day, month, year] = to_day_month_year(d);
        return month;
    }

    int GetYear() const {
        auto [day, month, year] = to_day_month_year(d);
        return year;
    }

    std::tuple<int, int, int> to_day_month_year(int n) const {
        int year = 1969;
        while (DaysInYear(year) <= n) {
            n -= DaysInYear(year);
            ++year;
        }
        int month = 1;
        while (DaysInMonth(month, year) <= n) {
            n -= DaysInMonth(month, year);
            ++month;
        }
        int day = n + 1;
        return std::make_tuple(day, month, year);
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

    int to_days(int day, int month, int year) const {
        int l = 0;
        int r = 100000;
        while (r - l > 1) {
            int m = (r + l) / 2;
            auto[da, mo, ye] = ToDate(m);
            if (std::make_tuple(ye, mo, da) > std::make_tuple(year, month, day)) {
                r = m;
            } else {
                l = m;
            }
        }
        return l;
    }

    static bool isLeapYear(int y) {
        return (y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0));
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

int main() {
    return 0;
}
