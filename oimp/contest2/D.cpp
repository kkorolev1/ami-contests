#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Date {
    int  day;
    int  hours;
    int  minutes;

    int in_minutes() const {
        return 60 * hours + minutes;
    }
};

istream& operator>>(istream& is, Date& date) {
    is >> date.day >> date.hours >> date.minutes;
    return is;
}

struct Alarm : Date {
    bool everyday() const {
        return day == 0;
    }

    void evaluate(const Date& date) {
        if (everyday()) {
            day = date.day;

            if (in_minutes() < date.in_minutes()) {
                day = 1 + (day % 7);
            }
        }
    }

    int timedelta(const Date& date) const {
        int alarm_day = day;

        if (day < date.day)
            alarm_day += 7 * (day < date.day);
        else if (day == date.day)
            alarm_day += 7 * (in_minutes() < date.in_minutes());

        auto day_to_minutes = [](int d) { return 24 * 60 * d; };
        int alarm_minutes = day_to_minutes(alarm_day) + in_minutes();
        int date_minutes = day_to_minutes(date.day) + date.in_minutes();
        return alarm_minutes - date_minutes;
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    Date today;
    cin >> today;

    int n;
    cin >> n;

    vector<Alarm> alarms(n);

    for (int i = 0; i < n; ++i) {
        cin >> alarms[i];
        alarms[i].evaluate(today);
    }

    auto ans = *min_element(alarms.begin(), alarms.end(),
            [&](const Alarm& lhs, const Alarm& rhs) {
        return lhs.timedelta(today) < rhs.timedelta(today);
    });

    cout << ans.day << " " << ans.hours << " " << ans.minutes;

    return 0;
}
