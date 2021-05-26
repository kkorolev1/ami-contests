#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

const int INF = numeric_limits<int>::max();

class Treap {
    static inline minstd_rand generator;

    struct Node {
        int priority, value, min;
        bool rev = false;
        Node *lhs = nullptr, *rhs = nullptr;
        int size;
        Node(int value) : value(value), min(value), priority(generator()), size(1) {}

    } *root = nullptr;

    static int getSize(Node* now) {
        return now ? now->size : 0;
    }

    static int getMin(Node* now) {
        return now ? now->min : INF;
    }

    static void update(Node *&now) {
        if (now) {
            now->size = getSize(now->lhs) + 1 + getSize(now->rhs);
            now->min = min(now->value, min(getMin(now->lhs), getMin(now->rhs)));
        }
    }

    static void reverse(Node *&now) {
        if (now->rev) {
            swap(now->lhs, now->rhs);

            if (now->lhs)
                now->lhs->rev ^= true;

            if (now->rhs)
                now->rhs->rev ^= true;

            now->rev = false;
        }
    }

    static Node *merge(Node *a, Node *b) {
        if (!a || !b) {
            return a ? a : b;
        }
        reverse(a);
        reverse(b);
        if (a->priority > b->priority) {
            a->rhs = merge(a->rhs, b);
            update(a);
            return a;
        } else {
            b->lhs = merge(a, b->lhs);
            update(b);
            return b;
        }
    }

    static void split(Node *now, int k, Node *&a, Node *&b) {
        if (!now) {
            a = b = nullptr;
            return;
        }
        reverse(now);

        if (getSize(now->lhs) < k) {
            split(now->rhs, k  - getSize(now->lhs) - 1, now->rhs, b);
            a = now;
        } else {
            split(now->lhs, k, a, now->lhs);
            b = now;
        }
        update(a);
        update(b);
    }

public:

    int get(int index) {
        Node *less, *great, *equal;
        split(root, index, less, great);
        split(great, 1, equal, great);
        int result = equal->value;
        root = merge(merge(less, equal), great);
        return result;
    }

    /*void insert(int key) {
        Node *less, *great;
        split(root, key, less, great);
        less = merge(less, new Node(key));
        root = merge(less, great);
    }

    void erase(int key) {
        Node *less, *great, *equal;
        split(root, key, less, great);
        split(great, key + 1, equal, great);
        root = merge(less, great);
    }*/

    void pushBack(int value) {
        root = merge(root, new Node(value));
    }

    void reverse(int l, int r) {
        Node *less, *equal, *great;
        split(root, l, less, great);
        split(great, r - l + 1, equal, great);
        equal->rev ^= true;
        root = merge(merge(less, equal), great);
    }

    int getMin(int l, int r) {
        Node *less, *equal, *great;
        split(root, l, less, great);
        split(great, r - l + 1, equal, great);
        int ans = getMin(equal);
        root = merge(merge(less, equal), great);
        return ans;
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    Treap t;

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        t.pushBack(a);
    }

    for (int i = 0; i < m; ++i) {
        int q, l, r;
        cin >> q >> l >> r;
        --l, --r;

        if (q == 1) {
            t.reverse(l, r);
        } else {
            cout << t.getMin(l, r) << "\n";
        }
    }

    return 0;
}
