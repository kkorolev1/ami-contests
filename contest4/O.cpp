#include <string>
struct Star {
    std::string name;
    uint64_t age;
};

#include <string>
#include <vector>
#include <map>
#include <algorithm>

std::string FindStar(const std::vector<Star>& stars) {
    auto median = stars.begin() + stars.size() / 2;
    std::nth_element(stars.begin(), median, stars.end());
    std::map<std::string, Star> unique_stars;

    for (auto& star : stars) {
        auto it = unique_stars.find(star.name);

        if (it == unique_stars.end()) {
            unique_stars.emplace(star.name, star);
        } else {
            it->second.age = std::max(it->second.age, star.age);
        }
    }

    return "foo";
}


#include <iostream>

using namespace std;

int main() {
    Star s1 {"OMEGA", 10};
    Star s2 {"OMEGA", 100};
    Star s3 {"ALPHA", 5};
    Star s4 {"ALPHA", 120};
    Star s5 {"ALPHA", 90};
    vector<Star> stars = {s1, s2, s3, s4, s5};
    cout << FindStar(stars) << "\n";
    return 0;
}
