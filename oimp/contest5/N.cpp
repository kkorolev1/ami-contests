#include <iostream>
#include <stdexcept>
#include <array>

#include <vector>
namespace sol {
    class Date {
    private:
        int day, month, year;

    public:
        bool IsLeap(int year) const {
            if (year % 400 == 0) {
                return true;
            } else if (year % 100 == 0) {
                return false;
            } else {
                return year % 4 == 0;
            }
        }

        int DaysInMonth(int month, int year) const {
            std::vector<int> days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (IsLeap(year)) {
                ++days[2];
            }
            return days[month];
        }

        Date(int day, int month, int year) : day(day), month(month), year(year) {
            if (!(1969 <= year && year <= 2100 &&
                  1 <= month && month <= 12 &&
                  1 <= day && day <= DaysInMonth(month, year))) {
                throw std::invalid_argument("Invalid date");
            }
        }

        int GetDay() const {
            return day;
        }

        int GetMonth() const {
            return month;
        }

        int GetYear() const {
            return year;
        }

        Date &operator++() {
            day += 1;
            if (day > DaysInMonth(month, year)) {
                day -= DaysInMonth(month, year);
                ++month;
                if (month > 12) {
                    month = 1;
                    ++year;
                }
            }
            return *this;
        }

        Date operator+(int plus) const {
            Date ans = Date(day, month, year);
            while (plus > 0) {
                ++ans;
                --plus;
            }
            return ans;
        }

        Date &operator--() {
            day -= 1;
            if (day == 0) {
                --month;
                if (month == 0) {
                    month = 12;
                    --year;
                }
                day = DaysInMonth(month, year);
            }
            return *this;
        }

        Date operator-(int plus) const {
            Date ans = Date(day, month, year);
            while (plus > 0) {
                --ans;
                --plus;
            }
            return ans;
        }

        // осталось сделать разницу
        std::tuple<int, int, int> getTuple() const {
            return std::make_tuple(year, month, day);
        }

        bool operator<(const Date &other) const {
            return getTuple() < other.getTuple();
        }

        bool operator==(const Date &other) const {
            return getTuple() == other.getTuple();
        }

        bool operator!=(const Date &other) const {
            return getTuple() != other.getTuple();
        }

        int operator-(const Date &other) const {
            if (*this == other) {
                return 0;
            }
            if (*this < other) {
                Date temp = Date(other.day, other.month, other.year);
                int ans = 0;
                while (temp != *this) {
                    ++ans;
                    --temp;
                }
                return ans*(-1);
            } else {
                Date temp = Date(day, month, year);
                int ans = 0;
                while (temp != other) {
                    ++ans;
                    --temp;
                }
                return ans;
            }
        }
    };
}

#include <iostream>
#include <stdexcept>
#include <array>

class Date {
public:
    Date(int _d, int _m, int _y) {
        if (_y < 1970 || _y > 2099)
            throw std::invalid_argument("Year is not in [1970; 2099]");
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
        Date res(*this);
        while (days--)
            ++res;
        return res;
    }

    Date operator-(int days) const {
        Date res(*this);
        while (days--)
            --res;
        return res;
    }

    int operator-(const Date& other) const {
        return dateToDays() - other.dateToDays();
    }

    /* bool operator==(const sol::Date& other) const {
        return y == other.GetYear() && m == other.GetMonth() && d == other.GetDay();
    } */

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

ostream& operator<<(ostream& os, const sol::Date& date) {
    os << setw(2) << setfill('0') << date.GetDay();
    os << "." << setw(2) << setfill('0') << date.GetMonth();
    os << "." << setw(4) << setfill('0') << date.GetYear();
    return os;
}


pair<Date, sol::Date> createDate(int d, int m, int y) {
    return make_pair(Date(d, m, y), sol::Date(d, m, y));
}

#include <random>

pair<Date, sol::Date> createDate() {
    random_device rd{};
    uniform_int_distribution<> ydist(1970, 2010);
    uniform_int_distribution<> mdist(1, 12);
    int y = ydist(rd);
    int m = mdist(rd);
    uniform_int_distribution<> ddist(1, Date::daysInMonth(m, y));
    int d = ddist(rd);
    return createDate(d, m, y);
}

template <typename T1, typename T2>
bool test(const T1& lhs, const T2& rhs) {
    if (lhs == rhs) {
        cout << "OK\n";
        return true;
    } else {
        cout << "WA\n";
        cout << lhs << " but correct is: " << rhs << "\n\n";
        return false;
    }
}


int main() {

    for (int i = 0; i < 100; ++i) {
        try {
            auto [d1, d3] = createDate();
            // auto [d2, d4] = createDate();
            int days = rand() % 10000;
            if (!test(d1 - days, d3 - days))
                cout << d1 << ", " << d3 << " + " << days << " days\n";
        } catch(...) {

        }
    }

    return 0;
}
