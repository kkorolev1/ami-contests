#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <iterator>

using namespace std;


int main() {
    freopen("input.txt", "r", stdin);

    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        int id, num_tasks;
        ss >> id >> num_tasks;
        bool in_numbers = true;

        vector<int> solved;

        string x;
        while (ss >> x) {
            if (isalpha(x.front())) {
                in_numbers = false;
                solved.push_back((x.front() - 'A') + 1);
            } else {
                solved.push_back(stoi(x));
            }
        }

        std::vector<int> all_tasks(num_tasks);
        iota(all_tasks.begin(), all_tasks.end(), 1);

        vector<int> unsolved;
        set_difference(all_tasks.begin(), all_tasks.end(),
                       solved.begin(), solved.end(), back_inserter(unsolved));

        cout << id;

        for (int task : unsolved) {
            cout << " ";

            if (in_numbers) {
                cout << task;
            } else {
                char c = (task - 1) + 'A';
                cout << c;
            }
        }

        cout << "\n";
    }

    return 0;
}
