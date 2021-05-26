#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    struct Node {
        Node(int x) : x(x), l(nullptr), r(nullptr) {}
        Node *l, *r;
        int x;
    } *root = nullptr;

    vector<int> values;

    void insert(Node*& node, int x) {
        if (!node) {
            node = new Node(x);
            return;
        }
        if (x <= node->x) {
            insert(node->l, x);
        } else {
            insert(node->r, x);
        }
    }

    void print(Node* node) {
        if (node) {
            print(node->l);
            values.push_back(node->x);
            print(node->r);
        }
    }

    /*int print(Node* node, Node* parent) {
        if (node) {
            int n = print(node->l, node);
            if (node->l || (parent && node->x != parent->x)) {
                cout << node->x << " " << (n > 0 ? n+1 : 1) << "\n";
            }
            print(node->r, node);
            if (parent && node->x == parent->x)
                return n + 1;
        }
        return 0;
    }*/

};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    Tree tree;

    while (true) {
        int x;
        cin >> x;
        if (x == 0)
            break;
        tree.insert(tree.root, x);
    }

    tree.print(tree.root);

    int n = 1;

    for (size_t i = 0; i + 1 < tree.values.size(); ++i) {
        if (tree.values[i] != tree.values[i + 1]) {
            cout << tree.values[i] << " " << n << "\n";
            n = 1;
        } else {
            ++n;
        }
    }

    cout << tree.values.back() << " " << n << "\n";

    return 0;
}
