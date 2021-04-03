#include <vector>
#include "writer.h"

class BufferedWriter : public Writer {
public:
    BufferedWriter(size_t bufferSize) {
        buffer.reserve(bufferSize);
    }

    ~BufferedWriter() {
        if (!buffer.empty()) {
            Writer::Write(buffer.data(), buffer.size());
        }
    }

    void Write(const char * data, size_t len) override {
        for (size_t i = 0; i < len; ++i) {
            WriteByte(data + i);
        }
    }

private:
    bool fullBuffer() const {
        return buffer.size() == buffer.capacity();
    }

    void WriteByte(const char* byte) {
        if (buffer.capacity() == 0) {
            Writer::Write(byte, 1);
            return;
        }

        if (fullBuffer()) {
            Writer::Write(buffer.data(), buffer.size());
            buffer.clear();
        }

        buffer.push_back(*byte);
    }

    std::vector<char> buffer;
};


#include <iostream>
using namespace std;

int main() {
    BufferedWriter w(2);
    w.Write("Hello, world!", 13);
    return 0;
}
