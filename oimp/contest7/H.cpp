#include <cmath>
#include <iostream>
#include <memory>
#include <string>

template <typename F>
class IntegrationMethod {
public:
    virtual double Integrate(F f, double a, double b, int n) const = 0;
    virtual ~IntegrationMethod() = default;
protected:
    static double getX(double a, double b, int k, int n) {
        return a + ((b - a) * k) / n;
    }
};

template <typename F>
class RectangleRule : public IntegrationMethod<F> {
public:
    double Integrate(F f, double a, double b, int n) const override {
        double res = 0;
        for (int k = 0; k < n; ++k) {
            double x1 = IntegrationMethod<F>::getX(a, b, k, n);
            double x2 = IntegrationMethod<F>::getX(a, b, k + 1, n);
            res += f((x1 + x2) / 2) * (x2 - x1);
        }
        return res;
    }
};

template <typename F>
class TrapezoidalRule : public IntegrationMethod<F> {
public:
    double Integrate(F f, double a, double b, int n) const override {
        double res = 0;
        for (int k = 0; k < n; ++k) {
            double x1 = IntegrationMethod<F>::getX(a, b, k, n);
            double x2 = IntegrationMethod<F>::getX(a, b, k + 1, n);
            res += (f(x1) + f(x2)) * (x2 - x1) / 2;
        }
        return res;
    }
};

int main() {
    using F = double(*)(double);

    std::string input;
    std::cin >> input;
    std::unique_ptr<IntegrationMethod<F>> method;
    if (input == "rectangle")
        method = std::make_unique<RectangleRule<F>>();
    else
        method = std::make_unique<TrapezoidalRule<F>>();

    double x, y;
    std::cin >> x >> y;

    int n;
    std::cin >> n;

    std::cout << method->Integrate(cos, x, y, n) << "\n";
    std::cout << method->Integrate(sin, x, y, n) << "\n";
}
