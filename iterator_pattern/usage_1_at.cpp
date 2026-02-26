#include <iostream>
#include <vector>

// ===== Iterator Interface =====
class Iterator { // [Iterator]
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

// ===== Aggregate Interface =====
class Aggregate { // [Aggregate]
public:
    virtual ~Aggregate() = default;
    virtual Iterator* createIterator() = 0;
};

// ===== ConcreteAggregate =====
class SensorCollection : public Aggregate { // [ConcreteAggregate]
private:
    std::vector<int> data;

public:
    void add(int value) {
        data.push_back(value);
    }

// ===== ConcreteIterator =====
class SensorIterator : public Iterator { // [ConcreteIterator]
    private:
        std::vector<int>& ref;
        size_t index = 0;

    public:
        SensorIterator(std::vector<int>& d) : ref(d) {}

        bool hasNext() override {
            return index < ref.size();
        }

        int next() override {
            return ref[index++];
    }
    };

    Iterator* createIterator() override {
        return new SensorIterator(data);
    }
};

int main() { // [Client]
    SensorCollection sensors;
    sensors.add(10);
    sensors.add(20);
    sensors.add(30);

    Iterator* it = sensors.createIterator();

    while (it->hasNext()) {
        std::cout << it->next() << "\n";
    }

    delete it;
    return 0;
}