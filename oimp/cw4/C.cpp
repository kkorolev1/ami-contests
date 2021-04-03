class Figure {
public:
    virtual ~Figure() = default;
    virtual int Perimeter() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c) : a(a), b(b), c(c) {}

    int Perimeter() const override {
        return a + b + c;
    }

private:
    int a, b, c;
};

class Rectangle : public Figure {
public:
    Rectangle(int width, int height) : w(width), h(height) {}

    int Perimeter() const override {
        return 2 * (w + h);
    }

private:
    int w, h;
};

#include <vector>
#include <iostream>

int main() {
    freopen("input.txt", "r", stdin);
    std::vector<Figure*> figures;
    std::string type;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }

    for (Figure* f : figures) {
        std::cout <<  f->Perimeter() <<  "\n";
    }

    for (Figure* f : figures) {
        delete f;
    }
}
