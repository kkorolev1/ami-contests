#include <iostream>
#include <list>

char read() {
    char c = '\0';
    std::cin >> c;
    return c;
}

void eat(size_t n) {
    for (size_t i = 0; i < n; ++i)
        read();
}

class Vim {
private:
    bool isEditMode_;
    std::list<char> text_;
    typename decltype(text_)::iterator cursor_;

public:
    Vim() : isEditMode_(false), cursor_(text_.begin()) {}

    void process(char c) {
        if (!isEditMode_) {
            if (c == 'i') {
                isEditMode_ = true;
            } else if (c == 'h' && cursor_ != text_.begin()) {
                --cursor_;
            } else if (c == 'l' && cursor_ != text_.end()) {
                ++cursor_;
            }
            return;
        }
        if (c == '<') {
            eat(4);
            isEditMode_ = false;
            return;
        }
        text_.insert(cursor_, c);
    }

    std::string getString() const {
        return std::string(text_.begin(), text_.end());
    }
};

using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    Vim vim;
    char c = read();

    while (c) {
        vim.process(c);
        c = read();
    }

    cout << vim.getString() << "\n";

    return 0;
}
