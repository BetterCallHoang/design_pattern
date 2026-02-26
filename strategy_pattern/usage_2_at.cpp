#include <iostream>

// ===== Strategy =====
class CompressionStrategy { // [Strategy]
public:
    virtual ~CompressionStrategy() = default;
    virtual void compress() = 0;
};

// ===== Concrete Strategies =====
class ZipCompression : public CompressionStrategy { // [ConcreteStrategy]
public:
    void compress() override {
        std::cout << "Compress using ZIP\n";
    }
};

class RarCompression : public CompressionStrategy { // [ConcreteStrategy]
public:
    void compress() override {
        std::cout << "Compress using RAR\n";
    }
};

// ===== Context =====
class Compressor { // [Context]
private:
    CompressionStrategy* strategy;

public:
    Compressor(CompressionStrategy* s) : strategy(s) {}

    void compress() {
        strategy->compress();
    }
};

int main() { // [Client]
    ZipCompression zip;
    Compressor c(&zip);
    c.compress();
}