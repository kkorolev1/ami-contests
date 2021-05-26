#include <iostream>
#include <vector>
using namespace std;

void print_error() {
    cout << "NO\n";
    exit(0);
}

struct RedBlackTree {
    RedBlackTree(int n) : left(n), right(n), key(n + 2), color(n + 2), n(n) {
        key[n] = numeric_limits<long long>::min();
        key[n+1] = numeric_limits<long long>::max();
        color[n] = color[n+1] = 'B';
    }

    // using Result = tuple<bool, int>;

    bool is_leaf(int i) {
        return i >= n;
    }

    int check(int i) {
        if (is_leaf(i)) {
            return 1;
        }

        if (color[i] != 'R' && color[i] != 'B') {
            print_error();
        }

        int li = left[i];
        int ri = right[i];

        if (key[li] >= key[ri] || key[li] >= key[i] || key[ri] <= key[i]) {
            print_error();
        }

        if (color[i] == 'R' && (color[li] == 'R' || color[ri] == 'R')) {
            print_error();
        }

        int bh_l = check(li);
        int bh_r = check(ri);

        if (bh_l != bh_r) {
            print_error();
        }

        return bh_l + (color[i] == 'B');
    }

    vector<int> left;
    vector<int> right;
    vector<long long> key;
    vector<char> color;
    int n;
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 0) {
        cout << "YES\n";
        return 0;
    }

    int root;
    cin >> root;
    --root;

    RedBlackTree tree(n);

    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        --number;

        cin >> tree.key[number];

        string x;

        cin >> x;
        tree.left[number] = x != "null" ? stoi(x) - 1 : n;

        cin >> x;
        tree.right[number] = x != "null" ? stoi(x) - 1 : n + 1;

        cin >> tree.color[number];
    }

    if (tree.color[root] == 'R') {
        print_error();
    }

    tree.check(root);
    cout << "YES\n";

    return 0;
}
