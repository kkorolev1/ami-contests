#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

class TooHardObjectException : public std::exception {
};

class MainClassifier {
public:
    explicit MainClassifier(const string& s)
            : data_(s)
    {
        cout << "Created MainClassifier()\n";
    }

    double classify(const string& s) {
        cout << "Called MainClassifier::classify(\"" << s << "\")\n";

        std::istringstream iss(s);
        vector<string> tokens{std::istream_iterator<string>{iss},
                              std::istream_iterator<string>{}};
        return std::stod(tokens[2]);
    }

private:
    string data_;
};

class FastClassifier {
public:
    explicit FastClassifier(const string& s)
            : data_(s)
    {
        cout << "Created FastClassifier()\n";
    }

    double classify(const string& s) {
        cout << "Called FastClassifier::classify(\"" << s << "\")\n";
        std::istringstream iss(s);
        vector<string> tokens{std::istream_iterator<string>{iss},
                              std::istream_iterator<string>{}};
        if (tokens[1] == "hard") {
            throw TooHardObjectException();
        } else {
            return std::stod(tokens[0]);
        }
    }

private:
    string data_;
};