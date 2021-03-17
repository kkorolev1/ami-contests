#include <map>
#include <string>
#include <vector>

struct Node {
    std::map<std::string, Node> children;
};

#include <iostream>
class Tree {
private:
    Node root;

public:
    bool Has(const std::vector<std::string>& node) const;

    void Insert(const std::vector<std::string>& node);

    void Delete(const std::vector<std::string>& node);

    /*void PrintNode(const Node& node, size_t level) {
        size_t childIdx = 0;
        for (auto [key, child] : node.children) {
            if (childIdx > 0) {
                for (size_t i = 0; i < level; ++i)
                    std::cout << " ";
            }
            std::cout << key << "/";
            PrintNode(child, level + key.size() + 1);
            ++childIdx;
        }
        std::cout << "\n";
    }

    void PrintTree() {
        PrintNode(root, 0);
    }*/
};


bool Tree::Has(const std::vector<std::string>& node) const {
    auto curNode = &root;
    for (const auto& folder : node) {
        auto it = curNode->children.find(folder);
        if (it == curNode->children.end())
            return false;
        curNode = &it->second;
    }
    return true;
}

void Tree::Insert(const std::vector<std::string>& node) {
    auto curNode = &root;
    for (const auto& folder : node) {
        auto it = curNode->children.find(folder);
        if (it == curNode->children.end()) {
            curNode = &curNode->children.emplace(folder, Node()).first->second;
        } else {
            curNode = &it->second;
        }
    }
}

void Tree::Delete(const std::vector<std::string>& node) {
    auto curNode = &root;
    for (auto nit = node.begin(); nit != node.end(); ++nit) {
        auto it = curNode->children.find(*nit);
        if (it == curNode->children.end())
            return;
        if (std::next(nit) == node.end()) {
            curNode->children.erase(it);
        } else {
            curNode = &it->second;
        }
    }
}

#include <iostream>
using namespace std;
#define check(expr, ans) \
if ((expr) != (ans)) { \
    cout << "Expression on line " << __LINE__ << ": " << #expr << "\n"; \
    cout << "Result: " << (expr) << "\n"; \
    cout << "Answer: " << (ans) << "\n"; \
    return; \
} \

void test() {
    Tree tree1;
    check(tree1.Has({}), true);
    check(tree1.Has({"~"}), false);
    tree1.Insert({"~"});
    check(tree1.Has({"~"}), true);
    tree1.Delete({"~"});
    check(tree1.Has({"~"}), false);

    tree1.Insert({"~", "kkorolev", "Desktop"});
    tree1.Insert({"~", "kkorolev", "Downloads"});

    check(tree1.Has({"~", "kkorolev", "Desktop"}), true);
    check(tree1.Has({"~", "kkorolev", "Downloads"}), true);
    check(tree1.Has({"~", "kkorolev-"}), false);
    check(tree1.Has({"~", "kkorolev", "Unknown"}), false);

    tree1.Insert({"~", "ymaximov"});
    check(tree1.Has({"~", "ymaximov"}), true);
    tree1.Delete({"~", "kkorolev"});
    check(tree1.Has({"~", "kkorolev", "Downloads"}), false);
    check(tree1.Has({"~", "kkorolev"}), false);
    tree1.Delete({"~", "kkorolev"});
    check(tree1.Has({"~", "ymaximov"}), true);

    // tree1.PrintTree();
}

int main() {
    test();
    return 0;
}
