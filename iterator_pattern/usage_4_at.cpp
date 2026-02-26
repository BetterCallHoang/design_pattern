#include <iostream>
#include <vector>

// ===== Iterator Interface =====
class Iterator { // [Iterator]
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual double next() = 0;
};

// ===== Aggregate Interface =====
class Aggregate { // [Aggregate]
public:
    virtual ~Aggregate() = default;
    virtual Iterator* createIterator() = 0;
};

// ===== ConcreteAggregate =====
class PowerCollection : public Aggregate { // [ConcreteAggregate]
private:
    std::vector<double> data;

public:
    void add(double v) {
        data.push_back(v);
    }

    // ===== ConcreteIterator =====
    class PowerIterator : public Iterator { // [ConcreteIterator]
    private:
        std::vector<double>& ref;
        size_t index = 0;

    public:
        PowerIterator(std::vector<double>& d) : ref(d) {}

        bool hasNext() override {
            return index < ref.size();
        }

        double next() override {
            return ref[index++];
        }
    };

    Iterator* createIterator() override {
        return new PowerIterator(data);
    }
};

int main() { // [Client]
    PowerCollection p;
    p.add(1.2);
    p.add(5.4);
    p.add(3.1);

    // ===== Business logic #1: compute sum =====
    Iterator* it1 = p.createIterator();
    double sum = 0;
    while (it1->hasNext())
        sum += it1->next();
    delete it1;

    std::cout << "Sum: " << sum << "\n";

    // ===== Business logic #2: find max =====
    Iterator* it2 = p.createIterator();
    double maxVal = -1e9;
    while (it2->hasNext()) {
        double v = it2->next();
        if (v > maxVal)
            maxVal = v;
    }
    delete it2;

    std::cout << "Max: " << maxVal << "\n";

    // ===== Business logic #3: filter =====
    Iterator* it3 = p.createIterator();
    std::cout << "Above 2.0:\n";
    while (it3->hasNext()) {
        double v = it3->next();
        if (v > 2.0)
            std::cout << v << "\n";
    }
    delete it3;

    return 0;
}