#include <iostream>

// ===== Strategy =====
class SortStrategy { // [Strategy]
public:
    virtual ~SortStrategy() = default;
    virtual void sort() = 0;
};

// ===== Concrete Strategies =====
class QuickSort : public SortStrategy { // [ConcreteStrategy]
public:
    void sort() override {
        std::cout << "QuickSort\n";
    }
};

class MergeSort : public SortStrategy { // [ConcreteStrategy]
public:
    void sort() override {
        std::cout << "MergeSort\n";
    }
};

// ===== Context =====
class Sorter { // [Context]
private:
    SortStrategy* strategy;

public:
    Sorter(SortStrategy* s) : strategy(s) {}

    void sort() {
        strategy->sort();
    }
};

int main() { // [Client]
    QuickSort quick;
    Sorter sorter(&quick);
    sorter.sort();
}