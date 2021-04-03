#include <stdexcept>
#include <optional>
#include <map>
#include <memory>


template <typename Key1, typename Key2, typename Value>
class BiMap {
public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text") в случае,
    // если оба ключа пусты, либо один из ключей уже имеется в хранилище.
    void Insert(const std::optional<Key1>& key1,
                const std::optional<Key2>& key2, const Value& value) {
        if (!key1 && !key2)
            throw std::invalid_argument("key1 and key2 are empty");

        if (key1 && mp1.find(key1.value()) != mp1.end())
            throw std::invalid_argument("key1 already exists");

        if (key2 && mp2.find(key2.value()) != mp2.end())
            throw std::invalid_argument("key2 already exists");

        std::shared_ptr<Value> valuePtr;

        if (key1) {
            valuePtr = std::make_shared<Value>(value);
            mp1.emplace(key1.value(), valuePtr);
        }

        if (key2) {
            if (!valuePtr) {
                valuePtr = std::make_shared<Value>(value);
            }
            mp2.emplace(key2.value(), valuePtr);
        }
    }

    // Получить значение по ключу первого типа.
    // Генерирует исключение std::out_of_range("some text")
    // в случае отсутствия ключа (как и функция at в std::map).
    Value& GetByPrimaryKey(const Key1& key) {
        return *mp1.at(key);
    }

    const Value& GetByPrimaryKey(const Key1& key) const {
        return *mp1.at(key);
    }

    // Аналогичная функция для ключа второго типа.
    Value& GetBySecondaryKey(const Key2& key) {
        return *mp2.at(key);
    }

    const Value& GetBySecondaryKey(const Key2& key) const {
        return *mp2.at(key);
    }

private:
    std::map<Key1, std::shared_ptr<Value>> mp1;
    std::map<Key2, std::shared_ptr<Value>> mp2;
};

#include <iostream>
#include <string>

using namespace std;

struct Student {
    string Surname, Name;
};

ostream& operator << (ostream& out, const Student& s) {
    return out << s.Surname << " " << s.Name;
}

/*void test(const BiMap<int, string, Student>& bimap) {
    bimap.GetByPrimaryKey(42).Name = "42";
    cout << bimap.GetByPrimaryKey(42) << "\n";
}*/

int main() {
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    bimap.GetByPrimaryKey(13).Name = "Oleg";  // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg

    bimap.Insert({14}, {"cshse-ami-999"}, {"Korolev", "Kirill"});
    cout << bimap.GetByPrimaryKey(14) << "\n";

    // bimap.Insert({}, {}, {"Kirill", "Korolev"});
    // cout << bimap.GetByPrimaryKey(43) << "\n";
    // cout << bimap.GetBySecondaryKey("cshse-ami-998") << "\n";

    /*BiMap<int, string, Student> bimap2;
    bimap2.Insert({1}, {"Kirill"}, {"Korolev", "Kirill"});
    auto& kir = bimap2.GetByPrimaryKey(1);
    kir.Surname = "Koroleff";
    cout << bimap2.GetByPrimaryKey(1) << "\n";
    cout << bimap2.GetBySecondaryKey("Kirill") << "\n";
    bimap2.GetBySecondaryKey("Kirill").Name = "Kirillich";
    cout << bimap2.GetByPrimaryKey(1) << "\n";
    cout << bimap2.GetBySecondaryKey("Kirill") << "\n";*/
    return 0;
}
