#include <deque>
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

void MakeTrain() {
    std::string line;
    std::deque<int> wagons;

    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    while (std::getline(std::cin, line)) {
        bool is_add_cmd = line[0] == '+';
        bool to_left = line[1] == 'l';
        auto it = std::find_if(line.begin(), line.end(),
                [](char c) { return std::isdigit(c); });
        int x = std::stoi(line.substr(it - line.begin()));

        if (is_add_cmd) {
            if (to_left) {
                wagons.push_front(x);
            } else {
                wagons.push_back(x);
            }
        } else {
            x = std::min(static_cast<size_t>(x), wagons.size());
            if (to_left) {
                wagons.erase(wagons.begin(), wagons.begin() + x);
            } else {
                wagons.resize(wagons.size() - x);
            }
        }
    }

    for (int x : wagons) {
        std::cout << x << " ";
    }

    std::cout << "\n";
}

#include <iostream>

using namespace std;

int main() {
    freopen("input1.txt", "r", stdin);
    MakeTrain();
    return 0;
}
