#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

const int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Exam {
    int d, m, y, t;
};

int main() {
    freopen("input.txt", "r", stdin);

    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Exam> exams(n);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        cin.get();

        auto& [d, m, y, t] = exams[i];

        getline(cin, s, '.');
        d = stoi(s);

        getline(cin, s, '.');
        m = stoi(s);

        getline(cin, s, '\n');
        y = stoi(s);

        cin >> t;
    }

    sort(exams.begin(), exams.end(), [](const Exam& e1, const Exam& e2) {
        return tie(e1.y, e1.m, e1.d) < tie(e2.y, e2.m, e2.d);
    });

    


    return 0;
}
