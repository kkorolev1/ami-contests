#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    unordered_set<string> set;

    string command;
    getline(cin, command);

    while (command != "#") {
        stringstream ss(command);
        string op, word;
        ss >> op >> word;

        if (op == "+") {
            set.insert(word);
        } else if (op == "-") {
            set.erase(word);
        } else {
            cout << (set.find(word) != set.end() ? "YES" : "NO") << "\n";
        }

        getline(cin, command);
    }

    return 0;
}
