#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    string path;
    set<string> folders;

    while (getline(cin, path)) {
        stringstream ss(path.substr(1));
        string atom;
        string current_path;

        while (getline(ss, atom, '/')) {
            current_path += '/' + atom;
            folders.insert(current_path + '/');
        }

        if (!current_path.empty()) {
            folders.erase(current_path + '/');
        }
    }

    if (!folders.empty()) {
        folders.insert("/");
    }

    for (auto& f : folders) {
        cout << f << "\n";
    }

    return 0;
}
