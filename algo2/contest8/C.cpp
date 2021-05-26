#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Treap {
    static inline minstd_rand generator;

    struct Node {
        int priority, value;
        long long sum;
        Node *lhs = nullptr, *rhs = nullptr;
        int size;
        Node(int value) : value(value), sum(value), priority(generator()), size(1) {}
        ~Node() {
            delete lhs;
            delete rhs;
        }

    } *root = nullptr;

    static int getSize(Node* now) {
        return now ? now->size : 0;
    }

    static long long getSum(Node* now) {
        return now ? now->sum : 0;
    }

    static void update(Node *&now) {
        if (now) {
            now->size = getSize(now->lhs) + getSize(now->rhs) + 1;
            now->sum = getSum(now->lhs) + getSum(now->rhs) + now->value;
        }
    }

    static Node *merge(Node *a, Node *b) {
        if (!a || !b) {
            return a ? a : b;
        }

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

    int get(int index) {
        Node *less, *great, *equal;
        split(root, index, less, great);
        split(great, 1, equal, great);
        int result = equal->value;
        root = merge(merge(less, equal), great);
        return result;
    }

    void pushBack(int value) {
        root = merge(root, new Node(value));
    }

    tuple<Node*, Node*, Node*> getInterval(int l, int r) {
        Node *less, *equal, *great;
        split(root, l - 1, less, great);
        split(great, r - l + 1, equal, great);
        return make_tuple(less, equal, great);
    }

    void merge(Node* less, Node* equal, Node* great) {
        root = merge(merge(less, equal), great);
    }

    ~Treap() {
        delete root;
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;
    int test = 1;

    while (n != 0 && m != 0) {
        Treap t1, t2;
        cout << "Swapper " << test << ":\n";

        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            if ((i % 2) == 0)
                t1.pushBack(a);
            else
                t2.pushBack(a);
        }

        for (int i = 0; i < m; ++i) {
            int q, l, r;
            cin >> q >> l >> r;

            int l1 = l / 2 + 1;
            int l2 = l / 2 + (l % 2);
            int r1 = r / 2 + (r % 2);
            int r2 = r / 2;

            auto [less1, equal1, great1] = t1.getInterval(l1, r1);
            auto [less2, equal2, great2] = t2.getInterval(l2, r2);

            if (q == 1) {
                t1.merge(less1, equal2, great1);
                t2.merge(less2, equal1, great2);
            } else {
                cout << Treap::getSum(equal1) + Treap::getSum(equal2) << "\n";
                t1.merge(less1, equal1, great1);
                t2.merge(less2, equal2, great2);
            }
        }

        cin >> n >> m;
        cout << "\n";
        ++test;
    }


    return 0;
}
