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

    Node* max(Node* node) {
        return node->r ? max(node->r) : node;
    }

    Node* prev(Node* node) {
        if (node->l) {
            return max(node->l);
        } else {
            while (node->p && node->p->l == node) {
                node = node->p;
            }
            return node->p;
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

    auto max = tree.max(tree.root);
    cout << tree.prev(max)->x << "\n";

    return 0;
}
