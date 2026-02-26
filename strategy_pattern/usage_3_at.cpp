#include <iostream>

// ===== Strategy =====
class FFTStrategy { // [Strategy]
public:
    virtual ~FFTStrategy() = default;
    virtual void compute() = 0;
};

// ===== Concrete Strategies =====
class StandardFFT : public FFTStrategy { // [ConcreteStrategy]
public:
    void compute() override {
        std::cout << "Standard FFT\n";
    }
};

class WindowedFFT : public FFTStrategy { // [ConcreteStrategy]
public:
    void compute() override {
        std::cout << "Windowed FFT\n";
    }
};

// ===== Context =====
class FFTProcessor { // [Context]
private:
    FFTStrategy* strategy;

public:
    FFTProcessor(FFTStrategy* s) : strategy(s) {}

    void setStrategy(FFTStrategy* s) {
        strategy = s;
    }

    void process() {
        strategy->compute();
    }
};

int main() { // [Client]
    StandardFFT stdFFT;
    WindowedFFT winFFT;

    FFTProcessor processor(&stdFFT);
    processor.process();

    processor.setStrategy(&winFFT);
    processor.process();
}