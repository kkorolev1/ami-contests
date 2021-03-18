#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expression() {}
};

using ExpressionPtr = std::shared_ptr<Expression>;

// Code
class ConstantExpression : public Expression {
public:
    ConstantExpression(int value) : value(value) {}

    int Evaluate() const override {
        return value;
    }

    std::string ToString() const override {
        return std::to_string(value);
    }

private:
    int value;
};

class SumExpression : public Expression {
public:
    SumExpression(const std::shared_ptr<Expression>& lhs, const std::shared_ptr<Expression>& rhs) :
        lhs(lhs), rhs(rhs) {}

    int Evaluate() const override {
        return lhs->Evaluate() + rhs->Evaluate();
    }

    std::string ToString() const override {
        return lhs->ToString() + " + " + rhs->ToString();
    }

private:
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;
};

class ProductExpression : public Expression {
public:
    ProductExpression(const std::shared_ptr<Expression>& lhs,
            const std::shared_ptr<Expression>& rhs) :
        lhs(lhs), rhs(rhs) {}

    int Evaluate() const override {
        return lhs->Evaluate() * rhs->Evaluate();
    }

    std::string ToString() const override {
        std::string lhsStr = lhs->ToString();
        std::string rhsStr = rhs->ToString();

        if (dynamic_cast<SumExpression*>(lhs.get())) {
            lhsStr = "(" + lhsStr + ")";
        }

        if (dynamic_cast<SumExpression*>(rhs.get())) {
            rhsStr = "(" + rhsStr + ")";
        }

        return lhsStr + " * " + rhsStr;
    }

private:
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;
};

std::shared_ptr<ConstantExpression> Const(int value) {
    return std::make_shared<ConstantExpression>(value);
}

std::shared_ptr<SumExpression> Sum(
        const std::shared_ptr<Expression>& lhs, const std::shared_ptr<Expression>& rhs) {
    return std::make_shared<SumExpression>(lhs, rhs);
}

std::shared_ptr<ProductExpression> Product(
        const std::shared_ptr<Expression>& lhs, const std::shared_ptr<Expression>& rhs) {
    return std::make_shared<ProductExpression>(lhs, rhs);
}

int main() {
    ExpressionPtr ex1 = Sum(Sum(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}
