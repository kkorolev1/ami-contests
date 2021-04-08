#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Enrollee {
    string name;
    string surname;
    tuple<int, int, int> birthdate;
    int points;
    vector<string> unis;
};

struct University {
    University(int max_studs) : free_places(max_studs) {}
    int free_places;
    vector<size_t> enrolled;
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    map<string, University> unis;

    for (int i = 0; i < n; ++i) {
        string uni;
        int max_studs;
        cin >> uni >> max_studs;
        unis.emplace(uni, max_studs);
    }

    int m;
    cin >> m;

    vector<Enrollee> enrollees(m);

    for (int i = 0; i < m; ++i) {
        auto& e = enrollees[i];
        cin >> e.name >> e.surname >>
            get<0>(e.birthdate) >> get<1>(e.birthdate) >>
            get<2>(e.birthdate) >> e.points;
        int k;
        cin >> k;

        e.unis.resize(k);

        for (int j = 0; j < k; ++j) {
            cin >> e.unis[j];
        }
    }

    sort(enrollees.begin(), enrollees.end(),
            [](const Enrollee& lhs, const Enrollee& rhs) {
        if (lhs.points != rhs.points) {
            return lhs.points > rhs.points;
        }
        if (lhs.birthdate != rhs.birthdate) {
            return lhs.birthdate < rhs.birthdate;
        }
        if (lhs.surname != rhs.surname) {
            return lhs.surname < rhs.surname;
        }
        return lhs.name < rhs.name;
    });

    for (size_t i = 0; i < enrollees.size(); ++i) {
        auto& e = enrollees[i];
        for (auto& u : e.unis) {
            auto it = unis.find(u);
            if (it != unis.end() && it->second.free_places > 0) {
                auto& uni = it->second;
                uni.enrolled.push_back(i);
                --uni.free_places;
                break;
            }
        }
    }

    for (auto& [name, u] : unis) {
        sort(u.enrolled.begin(), u.enrolled.end(), [&](size_t i, size_t j) {
            auto& lhs = enrollees[i];
            auto& rhs = enrollees[j];

            if (lhs.surname != rhs.surname) {
                return lhs.surname < rhs.surname;
            }

            if (lhs.name != rhs.name) {
                return lhs.name < rhs.name;
            }

            return lhs.birthdate < rhs.birthdate;
        });

        cout << name;

        for (size_t i : u.enrolled) {
            auto& e = enrollees[i];
            cout << "\t" << e.name << " " << e.surname;
        }

        cout << "\n";
    }

    return 0;
}
