#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>

using namespace std;

using Command = function<string(istream&, queue<int>&)>;

string push(istream& is, queue<int>& q) {
    int x;
    is >> x;
    q.push(x);
    return "ok";
}

string pop(istream&, queue<int>& q) {
    if (q.empty()) {
        return "error";
    }
    int x = q.front();
    q.pop();
    return to_string(x);
}

string front(istream&, queue<int>& q) {
    if (q.empty()) {
        return "error";
    }
    return to_string(q.front());
}

string size(istream&, queue<int>& q) {
    return to_string(q.size());
}

string clear(istream&, queue<int>& q) {
    while (!q.empty()) {
        q.pop();
    }

    return "ok";
}

string _exit(istream&, queue<int>&) {
    return "bye";
}

int main() {
    freopen("input.txt", "r", stdin);
    queue<int> q;
    string line;
    unordered_map<string, Command> cmds = {
            {"push", push}, {"pop", pop}, {"front", front},
            {"size", ::size}, {"clear", clear}, {"exit", _exit}};

    while (getline(cin, line)) {
        stringstream ss(line);
        string cmd_name;
        ss >> cmd_name;

        auto& cmd = cmds[cmd_name];
        auto response = cmd(ss, q);
        cout << response << "\n";

        if (response == "bye") {
            break;
        }
    }

    return 0;
}
