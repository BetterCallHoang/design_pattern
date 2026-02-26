/*Trường hợp 4: Muốn cho phép “Hook” – bước tùy chọn

Template Method cho phép có Hook method – subclass có thể override hoặc không.*/
#include <iostream>

// ===== AbstractClass =====
class TrainingProcess { // [AbstractClass]
public:
    void run() { // [Template Method]
        warmup();
        mainTraining();
        cooldown();
    }

protected:
    void warmup() { std::cout << "Warmup\n"; }

    virtual void mainTraining() = 0; // [Primitive Operation]

    virtual void cooldown() {        // [Hook]
        std::cout << "Default cooldown\n";
    }
};

// ===== ConcreteClass =====
class StrengthTraining : public TrainingProcess { // [ConcreteClass]
protected:
    void mainTraining() override {
        std::cout << "Lift weights\n";
    }
};

class CardioTraining : public TrainingProcess { // [ConcreteClass]
protected:
    void mainTraining() override {
        std::cout << "Run 5km\n";
    }

    void cooldown() override { // override Hook
        std::cout << "Stretching\n";
    }
};

int main() { // [Client]
    StrengthTraining a;
    CardioTraining b;

    a.run();
    b.run();

    return 0;
}