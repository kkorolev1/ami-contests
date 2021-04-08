#include <memory>
#include <optional>

namespace impl {
    template <typename T>
    class List {
        struct Node;
        using NodePtr = Node*;

        struct Node {
            Node() = default;
            Node(const T& value) : value(value) {}

            NodePtr prev = nullptr;
            NodePtr next = nullptr;
            std::optional<T> value;
        };

        class Iterator {
            NodePtr node;

        public:
            Iterator(NodePtr node) : node(node) {}

            Iterator& operator++() {
                node = node->next;
                return *this;
            }

            Iterator& operator++(int) {
                Iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            Iterator& operator--() {
                node = node->prev;
                return *this;
            }

            Iterator& operator--(int) {
                Iterator tmp(*this);
                --(*this);
                return tmp;
            }

            T& operator*() {
                return node->value.value();
            }

            const T& operator*() const {
                return node->value.value();
            }

            bool operator==(const Iterator& other) const {
                return node == other.node;
            }

            bool operator!=(const Iterator& other) const {
                return node != other.node;
            }

            NodePtr get() {
                return node;
            }
        };

        void reset(Iterator first, Iterator last) {
            auto it = first;

            while (it != last) {
                auto next = it;
                ++next;
                delete it.get();
                it = next;
            }
        }

        NodePtr head;
        size_t sz;

    public:
        List() : head(new Node()), sz(0) {}

        List(const List& other) : List() {
            try {
                for (auto jt = other.begin(); jt != other.end(); ++jt) {
                    push_back(*jt);
                }
            } catch (const std::exception& exc) {
                reset(begin(), end());
                head->prev = head->next = nullptr;
                sz = 0;
                throw exc;
            }
        }

        ~List() {
            reset(begin(), end());
            delete head;
        }

        List& operator=(const List& other) {
            if (this != &other) {
                auto prevFirst = head->next;
                auto prevLast = head->prev;
                auto prevSize = sz;

                try {
                    head->prev = head->next = nullptr;
                    sz = 0;
                    for (auto jt = other.begin(); jt != other.end(); ++jt) {
                        push_back(*jt);
                    }
                } catch (const std::exception& exc) {
                    reset(begin(), end());
                    head->prev = prevLast;
                    head->next = prevFirst;
                    sz = prevSize;
                    throw exc;
                }
            }
            return *this;
        }

        void push_back(const T& elem) {
            auto node = new Node(elem);
            if (!head->prev) {
                head->next = node;
                head->prev = node;
                node->prev = head;
                node->next = head;
            } else {
                node->prev = head->prev;
                head->prev->next = node;
                node->next = head;
                head->prev = node;
            }
            ++sz;
        }

        void push_front(const T& elem) {
            auto node = new Node(elem);
            if (!head->next) {
                head->next = node;
                head->prev = node;
                node->prev = head;
                node->next = head;
            } else {
                head->next->prev = node;
                node->next = head->next;
                head->next = node;
                node->prev = head;
            }
            ++sz;
        }

        void pop_back() {
            auto last = head->prev;
            last->prev->next = head;
            head->prev = last->prev;
            last->prev = last->next = nullptr;
            delete last;
            --sz;
        }

        void pop_front() {
            auto first = head->next;
            first->next->prev = head;
            head->next = first->next;
            first->prev = first->next = nullptr;
            delete first;
            --sz;
        }

        size_t size() const {
            return sz;
        }

        Iterator begin() const {
            return Iterator(head->next ? head->next : head);
        }

        Iterator end() const {
            return Iterator(head);
        }
    };
}

// using List = impl::List<int>;
using impl::List;

#include <iostream>
#include <list>

using namespace std;

struct A {
    A() { cout << "A()\n"; }
    A(const A&) { cout << "A(const A&)\n"; }
    A(A&&) { cout << "A(A&&)\n"; }
    ~A() { cout << "~A()\n"; }
};

int main() {
    using ListA = List<A>;
    using List = List<int>;
    ListA lsta;
    lsta.push_back(A());
    lsta.push_back(A());
    lsta.push_back(A());

    try {
        cout << "COPY CONSTRUCTOR\n";
        ListA lstb = lsta;
        lstb.pop_back();

        cout << "OPERATOR=\n";
        cout << "lsta.size() = " << lsta.size() << " lstb.size() = " << lstb.size() << "\n";
        lsta = lstb;
    } catch (...) {
        cout << "EXCEPTION\n";
    }

    cout << "DESTRUCTORS 2\n";
    return 0;

    List lst;
    lst.push_front(4);
    lst.push_front(3);
    lst.push_front(2);
    lst.push_front(1);
    lst.pop_back();
    lst.pop_front();

    cout << "Lst with size=" << lst.size() << "\n";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    cout << "Copying lst and changing lst2\n";
    auto lst2 = lst;

    for (auto it = lst2.begin(); it != lst2.end(); ++it) {
        *it = -*it;
    }

    cout << "Lst after changing in lst2\n";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }

    cout << "\n";

    cout << "Lst2\n";
    for (auto it = lst2.begin(); it != lst2.end(); ++it) {
        cout << *it << " ";
    }

    lst2 = lst;
    cout << "\n";
    cout << "Lst2 after operator=\n";
    for (auto it = lst2.begin(); it != lst2.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\nsize=" << lst2.size();
    cout << "\n";

    cout << "Lst3\n";
    List lst3;
    cout << "size=" << lst3.size() << "\n";

    lst3.push_front(1);
    lst3.push_back(5);
    lst3.push_front(0);
    lst3.push_back(6);
    lst3.push_front(-1);

    for (auto it = lst3.begin(); it != lst3.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    for (auto it = lst3.end(); it != lst3.begin(); ) {
        auto prev = --it;
        cout << *prev << " ";
    }

    return 0;
}
