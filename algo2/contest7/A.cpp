#include <iostream>

using namespace std;

struct Tree {
    struct Node {
        Node(int x) : x(x), l(nullptr), r(nullptr) {}
        Node *l, *r;
        int x;
    } *root = nullptr;

    void insert(Node*& node, int x) {
        if (node == nullptr) {
            node = new Node(x);
            return;
        }
        if (node->x == x)
            return;
        else if (x < node->x)
            insert(node->l, x);
        else
            insert(node->r, x);
    }

    int height(Node* node) {
        return node ? max(height(node->l), height(node->r)) + 1 : 0;
    }

};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("input.txt", "r", stdin);

    Tree tree;

    while (true) {
        int x;
        cin >> x;
        if (x == 0)
            break;
        tree.insert(tree.root, x);
    }

    cout << tree.height(tree.root) << "\n";

    return 0;
}
