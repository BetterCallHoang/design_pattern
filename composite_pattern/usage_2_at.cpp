#include <iostream>
#include <vector>

// ===== Component =====
class MenuComponent { // [Component]
public:
    virtual ~MenuComponent() = default;
    virtual void execute() = 0;
};

// ===== Leaf =====
class MenuItem : public MenuComponent { // [Leaf]
public:
    void execute() override {
        std::cout << "Execute action\n";
    }
};

// ===== Composite =====
class MenuGroup : public MenuComponent { // [Composite]
private:
    std::vector<MenuComponent*> children;

public:
    void add(MenuComponent* c) {
        children.push_back(c);
    }

    void execute() override {
        for (auto c : children)
            c->execute();
    }
};

int main() { // [Client]
    MenuItem item1;
    MenuItem item2;

    MenuGroup submenu;
    submenu.add(&item1);
    submenu.add(&item2);

    submenu.execute();
}