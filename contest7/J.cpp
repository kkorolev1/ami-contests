#include <iostream>
#include <vector>

class Model {
public:
    std::vector<int> data;

    void save(std::ostream& out) const;
    void load(std::istream& in);
};

template <typename Res, typename T>
Res cast(T t) {
    return reinterpret_cast<Res>(t);
}

void Model::save(std::ostream& out) const {
    size_t sz = data.size();
    out.write(cast<const char*>(&sz), sizeof(sz));
    for (size_t i = 0; i < sz; ++i) {
        out.write(cast<const char*>(&data[i]), sizeof(data[i]));
    }
}

void Model::load(std::istream& in) {
    size_t sz;
    in.read(cast<char*>(&sz), sizeof(sz));
    data.resize(sz);
    for (size_t i = 0; i < sz; ++i) {
        in.read(cast<char*>(&data[i]), sizeof(data[i]));
    }
}

#include <iostream>
#include <sstream>
#include <random>
#include <fstream>

int main() {
    // заклинание для ускорения потокового ввода-вывода
    std::ios::sync_with_stdio(false);

    Model m1;

    // как-то заполняем m1.data случайными числами
    const size_t n = 10;
    m1.data.resize(n);

    for (int i = 0; i < n; ++i) {
        m1.data[i] = i + 1;
    }

    std::ofstream os("file.txt", std::ios::binary);
    m1.save(os);
    os.close();

    std::ifstream is("file.txt", std::ios::binary);
    Model m2;
    m2.load(is);

    for (int x : m2.data) {
        std::cout << x << " ";
    }

    return 0;
}
