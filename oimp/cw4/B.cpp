#include <iostream>
#include <vector>
#include <memory>

class TreeNode {
private:
    int value;
    TreeNode* root = nullptr;
    using NodePtr = std::shared_ptr<TreeNode>;
    std::vector<NodePtr> children;
public:
    TreeNode(int val) : value(val) {}

    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    TreeNode* AddChild(int child_value) {
        auto node = std::make_shared<TreeNode>(child_value);
        node->root = this;
        children.push_back(node);
        return node.get();
    }

    void Print(int depth = 0) const {
        for (int i = 0; i < depth; ++i)
            std::cout << " ";
        std::cout << "- " << value << "\n";
        for (const auto& child : children)
            child->Print(depth + 1);
    }
};

int main() {
    TreeNode root(1);

    auto left_son = root.AddChild(10);
    auto middle_son = root.AddChild(20);
    auto right_son = root.AddChild(30);

    left_son->AddChild(100);
    left_son->AddChild(200);

    root.Print();
}
