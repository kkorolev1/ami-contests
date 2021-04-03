#include <map>
#include <string>
#include <iostream>

struct Student {
    std::string firstName;
    std::string lastName;
    std::map<std::string, double> marks;
    double rating;

    Student(const std::string& _firstName, const std::string& _lastName):
            firstName(_firstName),
            lastName(_lastName) {}

    bool operator < (const Student& other) const {
        return getName() < other.getName();
    }

    bool less(const Student& other) const {
        return rating > other.rating;
    }

    std::string getName() const {
        return firstName + " " + lastName;
    }
};

bool compare(const Student& one, const Student& two) {
    return one.less(two);
}

using namespace std;

int main() {
    return 0;
}
