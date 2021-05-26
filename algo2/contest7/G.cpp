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

    int height(Node* node, bool& is_avl) {
        if (node) {
            bool is_avl_l, is_avl_r;
            int hl = height(node->l, is_avl_l);
            int hr = height(node->r, is_avl_r);
            is_avl = is_avl_l && is_avl_r && (abs(hl - hr) <= 1);
            return max(hl, hr) + 1;
        }
        is_avl = true;
        return 0;
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

    bool is_avl;
    tree.height(tree.root, is_avl);
    cout << (is_avl ? "YES" : "NO") << "\n";

    return 0;
}
