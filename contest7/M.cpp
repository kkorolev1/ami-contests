#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out) {
    Serialize(str.size(), out);
    out.write(str.data(), str.size());
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& elem : data) {
        Serialize(elem, out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& [key, value] : data) {
        Serialize(key, out);
        Serialize(value, out);
    }
}

template <typename T>
void Deserialize(std::istream& in, T& pod) {
    in.read(reinterpret_cast<char*>(&pod), sizeof(pod));
}

void Deserialize(std::istream& in, std::string& str) {
    size_t str_size;
    Deserialize(in, str_size);
    str.resize(str_size);
    in.read(str.data(), str_size);
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t vec_size;
    Deserialize(in, vec_size);
    data.resize(vec_size);
    for (auto& elem : data) {
        Deserialize(in, elem);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t map_size;
    Deserialize(in, map_size);
    for (size_t i = 0; i != map_size; ++i) {
        T1 key;
        T2 value;
        Deserialize(in, key);
        Deserialize(in, value);
        data[key] = value;
    }
}