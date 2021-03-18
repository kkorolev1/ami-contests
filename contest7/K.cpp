#include <cstddef>  // for size_t
#include <iostream>

class RangeError {
};

size_t readSize(const char* data) {
    return *reinterpret_cast<const size_t*>(data);
}

const char* safeForward(const char* data, const char* end, size_t bytes) {
    if (data + bytes > end) {
        throw RangeError{};
    }
    return data += bytes;
}

size_t CountValues(const char * data, size_t size) {
    size_t numWords = 0;
    auto dataEnd = data + size;

    while (data != dataEnd) {
        size_t sz = readSize(data);
        data += sizeof(size_t);
        data = safeForward(data, dataEnd, sz * sizeof(char));
        ++numWords;
    }

    return numWords;
}

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ofstream ofs("file", std::ios::binary);
    vector<string> data = {"Hello", "it's", "me"};

    /*for (size_t i = 0; i < data.size(); ++i) {
        auto sz = data[i].size();
        auto str = data[i].c_str();
        ofs.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
        ofs.write(reinterpret_cast<const char*>(&str), sz * sizeof(char));
    }*/

    ofs.close();

    ifstream ifs("file", std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());

    auto sz = str.size();
    str.resize(str.size() - 3);
    cout << CountValues(str.c_str(), sz);

    return 0;
}
