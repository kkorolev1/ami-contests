#include <iostream>
#include <unordered_map>

using namespace std;

template <typename Key, typename Value>
class KeyValueStorage {
private:
    std::unordered_map<Key, Value> data;

public:
    void insert(const Key& key, const Value& value) {
        data[key] = value;
    }

    void remove(const Key& key) {
        data.erase(key);
    }

    bool find(const Key& key, Value * const value = nullptr) const;
};

template <typename Key, typename Value>
bool KeyValueStorage<Key, Value>::find(const Key& key, Value * const value) const {
    auto it = data.find(key);
    if (it == data.end())
        return false;
    if (value != nullptr)
        *value = it->second;
    return true;
}

#include <string>
int main() {
    KeyValueStorage<std::string, int> kv;
    kv.insert("hello", 42);
    kv.insert("bye", -13);
    int value = 123;
    auto res = kv.find("wrong", &value);  // должно вернуться false, а value не должен меняться
    cout << res << "\n";
    res = kv.find("bye", &value);  // должно вернуться true, в value должно быть -13
    cout << res << " " << value << "\n";
    res = kv.find("hello", nullptr);  // должно вернуться true
    cout << res << " " << value << "\n";
    return 0;
}
