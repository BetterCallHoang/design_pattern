#include <iostream>

// ===== Strategy Interface =====
class TaxStrategy { // [Strategy]
public:
    virtual ~TaxStrategy() = default;
    virtual double calculate(double amount) = 0;
};1

// ===== Concrete Strategies =====
class VietnamTax : public TaxStrategy { // [ConcreteStrategy]
public:
    double calculate(double amount) override {
        return amount * 0.1;
    }
};

class USTax : public TaxStrategy { // [ConcreteStrategy]
public:
    double calculate(double amount) override {
        return amount * 0.07;
    }
};

// ===== Context =====
class TaxCalculator { // [Context]
private:
    TaxStrategy* strategy;

public:
    TaxCalculator(TaxStrategy* s) : strategy(s) {}

    void setStrategy(TaxStrategy* s) {
        strategy = s;
    }

    double calculate(double amount) {
        return strategy->calculate(amount);
    }
};

int main() { // [Client]
    VietnamTax vn;
    USTax us;

    TaxCalculator calc(&vn);
    std::cout << calc.calculate(1000) << "\n";

    calc.setStrategy(&us); // đổi thuật toán runtime
    std::cout << calc.calculate(1000) << "\n";
}