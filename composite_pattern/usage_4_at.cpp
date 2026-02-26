#include <iostream>
#include <vector>

// ===== Component =====
class ProcessNode { // [Component]
public:
    virtual ~ProcessNode() = default;
    virtual void run() = 0;
};

// ===== Leaf =====
class SimpleStep : public ProcessNode { // [Leaf]
public:
    void run() override {
        std::cout << "Run simple step\n";
    }
};

// ===== Composite =====
class StepGroup : public ProcessNode { // [Composite]
private:
    std::vector<ProcessNode*> children;
public:
    void add(ProcessNode* n) {
        children.push_back(n);
    }

    void run() override {
        for (auto c : children)
            c->run();
    }
};

int main() { // [Client]
    SimpleStep step1;
    SimpleStep step2;

    StepGroup pipeline;
    pipeline.add(&step1);
    pipeline.add(&step2);

    pipeline.run();
}