#include <iostream>
#include <memory>
#include <string>

// Interface Component 
class Beverage {
public:
    virtual std::string getDesc() const = 0;
    virtual double getCost()      const = 0;
    virtual ~Beverage() = default;
};

// Concrete Components – các loại đồ uống gốc
class Espresso : public Beverage {
public:
    std::string getDesc() const override { return "Espresso"; }
    double getCost()      const override { return 20000; }
};
class Americano : public Beverage {
public:
    std::string getDesc() const override { return "Americano"; }
    double getCost()      const override { return 22000; }
};
//End of concrete conmponents

// Base Decorator – bọc Beverage và cũng là Beverage / Component Decorator 
class ToppingDecorator : public Beverage {
protected:
    std::unique_ptr<Beverage> beverage;
public:
    ToppingDecorator(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}
};

// Concrete Decorators – mỗi topping là 1 decorator
class Milk : public ToppingDecorator {
public:
    Milk(std::unique_ptr<Beverage> b) : ToppingDecorator(std::move(b)) {}

    std::string getDesc() const override {
        return beverage->getDesc() + " + Sữa";
    }
    double getCost() const override {
        return beverage->getCost() + 5000;
    }
};

class Sugar : public ToppingDecorator {
public:
    Sugar(std::unique_ptr<Beverage> b) : ToppingDecorator(std::move(b)) {}

    std::string getDesc() const override {
        return beverage->getDesc() + " + Đường";
    }
    double getCost() const override {
        return beverage->getCost() + 3000;
    }
};

class Cream : public ToppingDecorator {
public:
    Cream(std::unique_ptr<Beverage> b) : ToppingDecorator(std::move(b)) {}

    std::string getDesc() const override {
        return beverage->getDesc() + " + Kem";
    }
    double getCost() const override {
        return beverage->getCost() + 7000;
    }
};

// Thêm topping mới chỉ cần thêm 1 class – không sửa gì cả
class BubbleTea : public ToppingDecorator {
public:
    BubbleTea(std::unique_ptr<Beverage> b) : ToppingDecorator(std::move(b)) {}

    std::string getDesc() const override {
        return beverage->getDesc() + " + Trân Châu";
    }
    double getCost() const override {
        return beverage->getCost() + 10000;
    }
};

int main() {
    // Espresso thường
    std::unique_ptr<Beverage> drink = std::make_unique<Espresso>();
    std::cout << drink->getDesc() << " | " << drink->getCost() << " VND\n";

    // Espresso + Sữa + Đường
    drink = std::make_unique<Sugar>(
                std::make_unique<Milk>(
                    std::make_unique<Espresso>()));
    std::cout << drink->getDesc() << " | " << drink->getCost() << " VND\n";

    // Americano + Kem + Trân Châu + Sữa
    drink = std::make_unique<Milk>(
                std::make_unique<BubbleTea>(
                    std::make_unique<Cream>(
                        std::make_unique<Americano>())));
    std::cout << drink->getDesc() << " | " << drink->getCost() << " VND\n";
}
```

**Output:**
```
Espresso | 20000 VND
Espresso + Sữa + Đường | 28000 VND
Americano + Kem + Trân Châu + Sữa | 44000 VND