#include <iostream>

// ===== Component =====
class Expression { // [Component]
public:
    virtual ~Expression() = default;
    virtual int evaluate() = 0;
};

// ===== Leaf =====
class Number : public Expression { // [Leaf]
private:
    int value;
public:
    Number(int v) : value(v) {}
    int evaluate() override { return value; }
};

// ===== Composite =====
class Add : public Expression { // [Composite]
private:
    Expression* left;
    Expression* right;
public:
    Add(Expression* l, Expression* r) : left(l), right(r) {}
    int evaluate() override {
        return left->evaluate() + right->evaluate();
    }
};

class Multiply : public Expression { // [Composite]
private:
    Expression* left;
    Expression* right;
public:
    Multiply(Expression* l, Expression* r) : left(l), right(r) {}
    int evaluate() override {
        return left->evaluate() * right->evaluate();
    }
};

int main() { // [Client]
    Number three(3);
    Number five(5);
    Number two(2);

    Add add(&three, &five);
    Multiply expr(&add, &two);

    std::cout << expr.evaluate(); // 16
}