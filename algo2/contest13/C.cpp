#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<char> openedStack;
char opened[] = {'(', '['};
char closed[] = {')', ']'};

void rec(int i, int num_opened, string& ans) {
    if (i == ans.size()) {
        for (char c : ans) {
            cout << c;
        }
        cout << "\n";
        return;
    }

    if (2 * num_opened < ans.size()) {
        for (char c : opened) {
            ans[i] = c;
            openedStack.push(c);
            rec(i+1, num_opened+1, ans);
            openedStack.pop();
        }
    }

    for (int j = 0; j < 2; ++j) {
        if (!openedStack.empty() && opened[j] == openedStack.top()) {
            ans[i] = closed[j];
            openedStack.pop();
            rec(i+1, num_opened, ans);
            openedStack.push(opened[j]);
        }
    }
}

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n%2 == 0) {
        string ans(n, 0);
        rec(0, 0, ans);
    }

    return 0;
}
