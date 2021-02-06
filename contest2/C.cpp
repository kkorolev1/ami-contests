#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;
    int    birth_date[3];
};

bool compare_by_name(const Student& lhs, const Student& rhs) {
    if (lhs.surname != rhs.surname) {
        return lhs.surname < rhs.surname;
    }

    if (lhs.name != rhs.name) {
        return lhs.name < rhs.name;
    }

    return lexicographical_compare(lhs.birth_date, lhs.birth_date + 3,
            rhs.birth_date, rhs.birth_date + 3);
}

bool compare_by_birth_date(const Student& lhs, const Student& rhs) {
    if (!equal(lhs.birth_date, lhs.birth_date + 3, rhs.birth_date, rhs.birth_date + 3)) {
        return lexicographical_compare(lhs.birth_date, lhs.birth_date + 3,
                rhs.birth_date, rhs.birth_date + 3);
    }

    if (lhs.surname != rhs.surname) {
        return lhs.surname < rhs.surname;
    }

    return lhs.name < rhs.name;
}

int main() {
    int n;
    cin >> n;

    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        auto& s = students[i];
        cin >> s.name >> s.surname >> s.birth_date[2] >> s.birth_date[1] >> s.birth_date[0];
    }

    string type;
    cin >> type;

    if (type == "name") {
        sort(students.begin(), students.end(), compare_by_name);
    } else {
        sort(students.begin(), students.end(), compare_by_birth_date);
    }

    for (const auto& s : students) {
        cout << s.name << " " << s.surname << " "
        << s.birth_date[2] << "." << s.birth_date[1] << "." << s.birth_date[0] << "\n";
    }

    return 0;
}