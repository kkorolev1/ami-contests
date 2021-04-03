#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <queue>

using namespace std;

struct Word {
    Word(string _name, vector<int> _vec, int _index = 0) :
        name(move(_name)), vec(move(_vec)), prod(0), index(_index) {}
    string      name;
    vector<int> vec;
    long long   prod;
    int         index;
};

Word read_word(int n, int i = 0) {
    string name;
    cin >> name;

    vector<int> vec(n);

    for (int j = 0; j < n; ++j) {
        cin >> vec[j];
    }

    return Word(move(name), move(vec), i);
}

long long product(const Word& lhs, const Word& rhs) {
    return inner_product(lhs.vec.begin(), lhs.vec.end(),
                         rhs.vec.begin(), 0);
}

int main() {
    // freopen("input.txt", "r", stdin);
    int m, n;
    cin >> m >> n;

    auto first_word = read_word(n);

    auto cmp = [&](const Word& lhs, const Word& rhs) {
        if (lhs.prod != rhs.prod) {
            return lhs.prod < rhs.prod;
        }

        return lhs.index > rhs.index;
    };

    priority_queue<Word, vector<Word>, decltype(cmp)> words(cmp);

    for (int i = 1; i < m; ++i) {
        auto word = read_word(n, i);
        word.prod = product(first_word, word);
        words.emplace(move(word));
    }

    auto maximum = words.top();
    words.pop();

    cout << maximum.name << "\n";

    while (!words.empty()) {
        auto word = words.top();

        if (maximum.prod != word.prod) {
            break;
        }

        cout << word.name << "\n";
        words.pop();
    }

    return 0;
}
