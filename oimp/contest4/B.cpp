#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    string line;
    priority_queue<int> q;

    while (getline(cin, line)) {
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "ADD") {
            int n;
            ss >> n;
            q.push(n);
        } else if (cmd == "EXTRACT") {
            if (q.empty()) {
                cout << "CANNOT\n";
            } else {
                cout << q.top() << "\n";
                q.pop();
            }
        } else if (cmd == "CLEAR") {
            while (!q.empty()) {
                q.pop();
            }
        }
    }

    return 0;
}
