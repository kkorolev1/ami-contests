#include <iostream>

using namespace std;

struct Tree {
    struct Node {
        Node(int x) : x(x), l(nullptr), r(nullptr), p(nullptr) {}
        Node *l, *r, *p;
        int x;
    } *root = nullptr;

    void insert(Node*& node, int x) {
        if (!node) {
            node = new Node(x);
            return;
        }
        if (node->x == x)
            return;
        else if (x < node->x) {
            insert(node->l, x);
            if (!node->l->p)
                node->l->p = node;
        } else {
            insert(node->r, x);
            if (!node->r->p)
                node->r->p = node;
        }
    }

    void print(Node* node) {
        if (node) {
            print(node->l);
            if ((node->l && !node->r) || (!node->l && node->r))
                cout << node->x << "\n";
            print(node->r);
        }
    }
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

    return 0;
}
