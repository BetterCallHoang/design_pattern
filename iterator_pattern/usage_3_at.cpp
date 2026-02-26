#include <iostream>
#include <stack>

// ===== Iterator Interface =====
class Iterator { // [Iterator]
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

struct Node {
    int value;
    Node* left;
    Node* right;
};

// ===== ConcreteIterator =====
class InOrderIterator : public Iterator { // [ConcreteIterator]
private:
    std::stack<Node*> stack;

    void pushLeft(Node* node) {
        while (node) {
            stack.push(node);
            node = node->left;
        }
    }

public:
    InOrderIterator(Node* root) {
        pushLeft(root);
    }

    bool hasNext() override {
        return !stack.empty();
    }

    int next() override {
        Node* node = stack.top();
        stack.pop();
        pushLeft(node->right);
        return node->value;
    }
};

int main() { // [Client]
    Node n1{1,nullptr,nullptr};
    Node n2{2,nullptr,nullptr};
    Node root{3,&n1,&n2};

    InOrderIterator it(&root);

    while (it.hasNext()) {
        std::cout << it.next() << "\n";
    }

    return 0;
}