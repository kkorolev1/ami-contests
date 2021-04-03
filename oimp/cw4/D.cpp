#include <string>

unsigned int CharToInt(unsigned char c) {
    return static_cast<unsigned int>(c);
}

bool IsPDF(const unsigned char* data, size_t size) {
    if (size < 4)
        return false;
    return (CharToInt(data[0]) == 0x25) && (CharToInt(data[1]) == 0x50) &&
            (CharToInt(data[2]) == 0x44) && (CharToInt(data[3]) == 0x46);
}

bool IsJPEG(const unsigned char* data, size_t size) {
    if (size < 3)
        return false;
    return (CharToInt(data[0]) == 0xff) && (CharToInt(data[1]) == 0xd8) &&
            (CharToInt(data[2]) == 0xff);
}

bool IsZIP(const unsigned char* data, size_t size) {
    if (size < 2)
        return false;
    return (CharToInt(data[0]) == 0x50) && (CharToInt(data[1]) == 0x4b);
}

std::string DetectType(const unsigned char* data, size_t size) {
    if (IsPDF(data, size))
        return "pdf";
    else if (IsJPEG(data, size))
        return "jpg";
    else if (IsZIP(data, size))
        return "zip";
    else
        return "other";
}

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const size_t size = 1024;

    unsigned char file2[size] = {0xff, 0xd8, 0xff};
    cout << DetectType(file2, size) << "\n";

    unsigned char file1[size] = {0x25, 0x50, 0x44, 0x46};
    cout << DetectType(file1, size) << "\n";

    unsigned char file12[size] = {0x25, 0x50, 0x44, 0x46};
    cout << DetectType(file12, 3) << "\n";

    unsigned char file13[size] = {0x25, 0x50, 0x43, 0x46};
    cout << DetectType(file13, 4) << "\n";

    unsigned char file22[size] = {0xff, 0xd7, 0xff};
    cout << DetectType(file22, size) << "\n";

    unsigned char file3[size] = {0x50, 0x4b};
    cout << DetectType(file3, size) << "\n";

    unsigned char file31[size] = {0x50, 0x4b};
    cout << DetectType(file31, 0) << "\n";

    unsigned char file32[size] = {0x50, 0x3b};
    cout << DetectType(file32, 0) << "\n";

    return 0;
}
