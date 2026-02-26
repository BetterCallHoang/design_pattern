#include <iostream>
#include <vector>

// ===== Iterator Interface =====
class Iterator { // [Iterator]
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

// ===== ConcreteAggregate =====
class NumberCollection { // [ConcreteAggregate]
private:
    std::vector<int> data;

public:
    void add(int v) { data.push_back(v); }

    // Forward Iterator
    class ForwardIterator : public Iterator { // [ConcreteIterator]
        std::vector<int>& ref;
        size_t index = 0;
    public:
        ForwardIterator(std::vector<int>& d) : ref(d) {}
        bool hasNext() override { return index < ref.size(); }
        int next() override { return ref[index++]; }
    };

    // Reverse Iterator
    class ReverseIterator : public Iterator { // [ConcreteIterator]
        std::vector<int>& ref;
        int index;
    public:
        ReverseIterator(std::vector<int>& d)
            : ref(d), index(d.size() - 1) {}
        bool hasNext() override { return index >= 0; }
        int next() override { return ref[index--]; }
    };

    Iterator* createForwardIterator() {
        return new ForwardIterator(data);
    }

    Iterator* createReverseIterator() {
        return new ReverseIterator(data);
    }
};

int main() { // [Client]
    NumberCollection nums;
    nums.add(1);
    nums.add(2);
    nums.add(3);

    Iterator* it = nums.createReverseIterator();

    while (it->hasNext()) {
        std::cout << it->next() << "\n";
    }

    delete it;
    return 0;
}