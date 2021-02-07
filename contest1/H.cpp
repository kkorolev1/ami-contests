#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int transform_consonant(char c) {
    switch (c) {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
            return 1;
        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
            return 2;
        case 'd':
        case 't':
            return 3;
        case 'l':
            return 4;
        case 'm':
        case 'n':
            return 5;
        case 'r':
            return 6;
    }
    return 0;
}

int main() {
    string word;
    cin >> word;
    string transformed_word(1, word.front());
    const string vowels = "aehiouwy";
    int prev_code = 0;

    for (size_t i = 1; i < word.size(); ++i) {
        if (vowels.find(word[i]) == string::npos) {
            auto code = transform_consonant(word[i]);
            if (code != prev_code) {
                transformed_word += to_string(code);
                prev_code = code;
            }
        }
    }

    const int length = 4;

    if (transformed_word.size() < length) {
        transformed_word.append(length - transformed_word.size(), '0');
    } else if (transformed_word.size() > length) {
        transformed_word.resize(4);
    }

    cout << transformed_word << "\n";

    return 0;
}
