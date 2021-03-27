#include <memory>
#include <algorithm>

namespace impl {

    template <typename T>
    class Vector {
        struct Buffer {
            static T* allocate(size_t n) {
                return static_cast<T*>(operator new(n * sizeof(T)));
            }

            static void deallocate(T* data) {
                return operator delete(data);
            }

            Buffer(size_t n) : data(allocate(n)), cp(n) {}

            Buffer(const Buffer&) = delete;

            Buffer(Buffer&& other) {
                swap(other);
            }

            ~Buffer() {
                deallocate(data);
            }

            T* operator+(size_t i) {
                return data + i;
            }

            const T* operator+(size_t i) const {
                return data + i;
            }

            T& operator[](size_t i) {
                return data[i];
            }

            const T& operator[](size_t i) const {
                return data[i];
            }

            void swap(Buffer& other) {
                std::swap(data, other.data);
                std::swap(cp, other.cp);
            }

            T* data;
            size_t cp;
        };

        Buffer buf;
        size_t sz;

    public:
        Vector(size_t n = 0) : buf(n), sz(n) {
            std::uninitialized_value_construct_n(buf.data, n);
        }

        Vector(const Vector& other) : buf(other.sz), sz(other.sz) {
            std::uninitialized_copy_n(other.buf.data, other.sz, buf.data);
        }

        Vector& operator=(const Vector& other) {
            if (other.sz > buf.cp) {
                Vector tmp(other);
                swap(tmp);
            } else {
                std::copy_n(other.buf.data, std::min(sz, other.sz), buf.data);

                if (sz < other.sz) {
                    std::uninitialized_copy_n(other.buf.data + sz,
                            other.sz - sz, buf.data + sz);
                } else {
                    std::destroy_n(buf.data + other.sz, sz - other.sz);
                }
                sz = other.sz;
            }
            return *this;
        }

        ~Vector() {
            std::destroy_n(buf.data, sz);
        }

        void push_back(const T& elem) {
            if (buf.cp == sz) {
                reserve(sz > 0 ? 2 * buf.cp : 1);
            }
            new (buf + sz) T(elem);
            ++sz;
        }

        void push_back(T&& elem) {
            if (buf.cp == sz) {
                reserve(sz > 0 ? 2 * buf.cp : 1);
            }
            new (buf + sz) T(std::move(elem));
            ++sz;
        }

        void pop_back() {
            std::destroy_at(buf + sz - 1);
            --sz;
        }

        size_t size() const {
            return sz;
        }

        T& operator[](size_t idx) {
            return buf[idx];
        }

        const T& operator[](size_t idx) const {
            return buf[idx];
        }

        void reserve(size_t n) {
            if (n > buf.cp) {
                Buffer buf2(n);
                std::uninitialized_move_n(buf.data, sz, buf2.data);
                std::destroy_n(buf.data, sz);
                buf.swap(buf2);
            }
        }

        void swap(Vector& other) {
            buf.swap(other.buf);
            std::swap(sz, other.sz);
        }

        size_t capacity() const {
            return buf.cp;
        }

        void resize(size_t n) {
            reserve(n);

            if (sz < n) {
                std::uninitialized_value_construct_n(buf + sz, n - sz);
            } else if (sz > n) {
                std::destroy_n(buf + n, sz - n);
            }

            sz = n;
        }

        void clear() {
            resize(0);
        }

        using Iterator = T*;
        using ConstIterator = const T*;

        Iterator begin() {
            return buf.data;
        }

        Iterator end() {
            return buf + sz;
        }

        ConstIterator begin() const {
            return buf.data;
        }

        ConstIterator end() const {
            return buf + sz;
        }
    };
}

using impl::Vector;

/*#include <iostream>

using namespace std;

int main() {
    Vector<int> v;

    v.push_back(42);
    cout << v[0] << "\n";
    cout << v.size() << "\n";
    v.pop_back();
    cout << v.size() << "\n";
    v.push_back(43);
    v.push_back(44);
    v.push_back(45);
    v.push_back(46);
    v.push_back(47);
    v.push_back(48);

    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";

    v.pop_back();
    v.pop_back();
    v.pop_back();

    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";

    Vector<int> u(v);
    u.pop_back();

    for (int i = 0; i < u.size(); ++i) {
        cout << u[i] << " ";
    }
    cout << "\n";

    v = u;
    v.push_back(120);

    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";

    Vector<int> f;
    f.push_back(1);
    f = v;

    for (int i = 0; i < f.size(); ++i) {
        cout << f[i] << " ";
    }
    cout << "\n";

    return 0;
}*/

#include <deque>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>

// #define USE_STD_VECTOR

#ifdef USE_STD_VECTOR
template <typename T>
    using Vector = std::vector<T>;
#endif

using i32 = std::int32_t;

class C {
public:
    std::string val;
    i32 id{};

    inline static i32 counter{};

    C(const std::string& s = "(empty)")
            : val{s}, id{++counter} {
        if (id == 26) {
            throw std::runtime_error("No ways to construct 26th class C object.");
        }
    }

    C(const C& other)
            : val{other.val}, id{++counter} {
    }

    C& operator=(const C& other) {
        val = other.val;
        return *this;
    }

    ~C() {
        std::cout << "C destructor called\n";
    }
};

template <typename T>
void Print(const Vector<T>& vector) {
    std::cout << "size: " << std::setw(3) << vector.size() << '\t'
              << "capacity: " << std::setw(3) << vector.capacity() << '\n'
              << C::counter << '\n';
}

int main() {
    static_assert(sizeof(Vector<C>) <= sizeof(C*) * 3);
    static_assert(!std::is_constructible<std::deque<C>, Vector<C>>::value);

#ifndef USE_STD_VECTOR
    static_assert(!std::is_constructible<std::vector<C>, Vector<C>>::value);
#endif

    {
        Vector<i32> vec(5);
        Print(vec);
        for (auto& elem : vec) {  // begin && end
            elem = 1;
        }

        const Vector<i32> otherVec(vec);
        for (size_t i = 0; i != otherVec.size(); ++i) {
            std::cout << otherVec[i] << ' ';
        }
        std::cout << '\n';

        vec.push_back(2);
        vec.push_back(3);
        Print(vec);
        vec.resize(2);
        Print(vec);
        Vector<i32> reallyOtherVector;
        Print(reallyOtherVector);
        reallyOtherVector = vec;
        Print(reallyOtherVector);
    }
    std::cout << '\n';

    {Vector<C> vec(5);}
    std::cout << '\n';

    C c("My vector work!");
    C c2("My vector still work!");
    std::cout << '\n';

    {
        Vector<C> vec(3);
        vec.reserve(7);
        vec.push_back(c);
        vec.pop_back();
        Print(vec);
        vec.clear();
        Print(vec);
        std::cout << "clear done\n";
    }
    std::cout << '\n';

    {
        Vector<C> vec;
        vec.push_back(c);
        Print(vec);
        vec.push_back(c2);
        Print(vec);
        vec.resize(5);
        Print(vec);

        Vector<C> otherVec;
        try {
            otherVec.resize(10);
        } catch (const std::runtime_error& error) {
            std::cout << error.what() << '\n';
        }
        std::cout << otherVec.size() << '\n';
    }
    std::cout << '\n';

    std::cout << "Tests done, C objects die here:\n";
}
