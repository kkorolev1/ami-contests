#include <map>
#include <iostream>
#include <string>
#include <vector>


// Для простых примитивных типов (int, bool, char и т. д.) и plain old data
template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);



template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

#include <fstream>
using namespace std;

struct GameObject {
    int x;
    int y;
};

int main() {
    GameObject obj{4, 8};

    ofstream os("file", ios::binary);
    Serialize(obj, os);

    return 0;
}
