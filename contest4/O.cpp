#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

struct Star {
    std::string name;
    uint64_t age;
};

struct StarCmp {
    bool operator()(const Star& lhs, const Star& rhs) const {
        return lhs.name < rhs.name;
    }
};

std::string FindStar(const std::vector<Star>& stars) {
    std::unordered_map<std::string, Star> unique_stars;

    for (auto& star : stars) {
        auto it = unique_stars.find(star.name);

        if (it == unique_stars.end()) {
            unique_stars.emplace(star.name, star);
        } else {
            it->second.age = std::max(it->second.age, star.age);
        }
    }

    std::vector<Star> unique_stars_v;
    std::transform(unique_stars.begin(), unique_stars.end(), std::back_inserter(unique_stars_v),
            [](const std::pair<std::string, Star>& p) {
        return p.second;
    });

    std::nth_element(unique_stars_v.begin(), unique_stars_v.begin() + unique_stars_v.size() / 2,
            unique_stars_v.end(), [](const Star& lhs, const Star& rhs) {
        return lhs.age < rhs.age;
    });

    auto median_age = unique_stars_v[unique_stars_v.size() / 2].age;

    std::set<Star, StarCmp> ans;
    std::copy_if(unique_stars_v.begin(), unique_stars_v.end(), std::inserter(ans, ans.begin()),
    [&](const Star& star) {
        return star.age == median_age;
    });

    return ans.begin()->name;
}


#include <iostream>

using namespace std;

int main() {
    Star s5 {"A", 50};
    Star s6 {"L", 30};
    Star s7{"L", 60};
    Star s3 {"K", 10};
    Star s4 {"E", 90};

    // 10 50 60 90

    vector<Star> stars = {s3, s4, s5, s6, s7};
    cout << FindStar(stars) << "\n";
    return 0;
}
