/*✔ Client không biết class cụ thể
✔ Đảm bảo Button và Checkbox cùng “hệ”*/

#include <iostream>

// ===== Abstract Products =====
class Button { // [AbstractProduct]
public:
    virtual ~Button() = default;
    virtual void draw() = 0;
};

class Checkbox { // [AbstractProduct]
public:
    virtual ~Checkbox() = default;
    virtual void draw() = 0;
};

// ===== Concrete Products =====
class WinButton : public Button { // [ConcreteProduct]
public:
    void draw() override { std::cout << "Draw Windows Button\n"; }
};

class WinCheckbox : public Checkbox { // [ConcreteProduct]
public:
    void draw() override { std::cout << "Draw Windows Checkbox\n"; }
};

class LinuxButton : public Button { // [ConcreteProduct]
public:
    void draw() override { std::cout << "Draw Linux Button\n"; }
};

class LinuxCheckbox : public Checkbox { // [ConcreteProduct]
public:
    void draw() override { std::cout << "Draw Linux Checkbox\n"; }
};

// ===== Abstract Factory =====
class GUIFactory { // [AbstractFactory]
public:
    virtual ~GUIFactory() = default;
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
};

// ===== Concrete Factories =====
class WinFactory : public GUIFactory { // [ConcreteFactory]
public:
    Button* createButton() override { return new WinButton(); }
    Checkbox* createCheckbox() override { return new WinCheckbox(); }
};

class LinuxFactory : public GUIFactory { // [ConcreteFactory]
public:
    Button* createButton() override { return new LinuxButton(); }
    Checkbox* createCheckbox() override { return new LinuxCheckbox(); }
};

// ===== Client =====
int main() {
    GUIFactory* factory = new WinFactory(); // chỉ chọn 1 lần

    Button* btn = factory->createButton();
    Checkbox* chk = factory->createCheckbox();

    btn->draw();
    chk->draw();

    delete btn;
    delete chk;
    delete factory;

    return 0;
}