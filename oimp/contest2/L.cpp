#include <string>

std::pair<size_t, size_t> FindVowels(const std::string& str, size_t pos) {
    const std::string vowels = "aeiouyAEIOUY";
    size_t start = str.find_first_of(vowels, pos);

    if (start == std::string::npos) {
        return std::make_pair(start, 0);
    }

    size_t end = str.find_first_not_of(vowels, start);
    return std::make_pair(start,
            (end != std::string::npos) ? (end - start) : str.size() - start);
}

#include <iostream>

using namespace std;

int main() {
    string text;
    getline(cin, text);
    size_t pos = 0;
    while (true) {
        auto [start, length] = FindVowels(text, pos);
        if (start == string::npos)
            break;
        cout << start << " " << length << " " << text.substr(start, length) << "\n";
        pos = start + length;
    }
    return 0;
}