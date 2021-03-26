#include <memory>
#include <optional>

namespace impl {
    template <typename T>
    class List {
        struct Node;
        using NodePtr = std::shared_ptr<Node>;

        struct Node {
            Node() = default;
            Node(const T& value) : value(value) {}

            NodePtr prev;
            NodePtr next;
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
        };

        NodePtr head;
        size_t sz;

    public:
        List() {
            auto dummyNode = std::make_shared<Node>();
            head = dummyNode;
            sz = 0;
        }

        List(const List& other) : List() {
            for (auto it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }

        ~List() = default;

        List& operator=(const List& other) {
            if (this != &other) {
                head->prev = head->next = nullptr;
                sz = 0;

                for (auto it = other.begin(); it != other.end(); ++it) {
                    push_back(*it);
                }
            }
            return *this;
        }

        void push_back(const T& elem) {
            auto node = std::make_shared<Node>(elem);
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
            auto node = std::make_shared<Node>(elem);
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
            if (head->prev) {
                auto last = head->prev;
                last->prev->next = head;
                head->prev = last->prev;
                --sz;
            }
        }

        void pop_front() {
            if (head->next) {
                auto first = head->next;
                first->next->prev = head;
                head->next = first->next;
                --sz;
            }
        }

        size_t size() const {
            return sz;
        }

        Iterator begin() {
            return Iterator(head->next ? head->next : head);
        }

        Iterator end() {
            return Iterator(head);
        }

        Iterator begin() const {
            return Iterator(head->next ? head->next : head);
        }

        Iterator end() const {
            return Iterator(head);
        }
    };
}

using List = impl::List<int>;

#include <iostream>

using namespace std;

int main() {
    List lst;
    /*lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.pop_back();
    lst.push_front(0);
    */
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
