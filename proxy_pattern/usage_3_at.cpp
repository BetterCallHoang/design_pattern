#include <iostream>

// ===== Subject =====
class IProcessor { // [Subject]
public:
    virtual ~IProcessor() = default;
    virtual void process() = 0;
};

// ===== RealSubject =====
class DataProcessor : public IProcessor { // [RealSubject]
public:
    void process() override {
        std::cout << "Processing data\n";
    }
};

// ===== Proxy =====
class LoggingProxy : public IProcessor { // [Proxy]
private:
    IProcessor* real;

public:
    LoggingProxy(IProcessor* r) : real(r) {}

    void process() override {
        std::cout << "[LOG] Before processing\n";
        real->process();
        std::cout << "[LOG] After processing\n";
    }
};

int main() { // [Client]
    DataProcessor real;
    LoggingProxy proxy(&real);

    proxy.process();
}

