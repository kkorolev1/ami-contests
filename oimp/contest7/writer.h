#include <cstddef>
#include <iostream>
#include <string>

using std::cout;

class Writer {
public:
    virtual void Write(const char * data, size_t len) {
        // Какой-то вывод в файл, на экран или в память
        cout << std::string(data, len) << "\n";
    }
};
