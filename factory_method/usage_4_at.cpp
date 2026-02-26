

#include <iostream>
#include <memory>

// Product – do framework định nghĩa
class Button {
public:
    virtual void render() const = 0;
    virtual void onClick() const = 0;
    virtual ~Button() = default;
};

// Framework cung cấp sẵn một số implementation
class WindowsButton : public Button {
public:
    void render()  const override { std::cout << "Render [Windows Button]\n"; }
    void onClick() const override { std::cout << "Click  [Windows style]\n"; }
};

// Người dùng framework tự thêm implementation của họ
class MacButton : public Button {
public:
    void render()  const override { std::cout << "Render [Mac Button]\n"; }
    void onClick() const override { std::cout << "Click  [Mac style]\n"; }
};

// Creator – framework định nghĩa, để createButton() là abstract
// → người dùng override để "cắm" Button của họ vào
class Application {
public:
    virtual std::unique_ptr<Button> createButton() const = 0;

    // Toàn bộ logic render của framework – không đổi dù Button là gì
    void buildUI() const {
        std::cout << "Khởi tạo UI...\n";
        auto btn = createButton(); // framework gọi factory method
        btn->render();
        btn->onClick();
    }
    virtual ~Application() = default;
};

// Người dùng framework: chỉ cần subclass Application
// và override createButton() → xong, không cần sửa gì trong framework
class WindowsApp : public Application {
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
};

class MacApp : public Application {
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
};

int main() {
    WindowsApp winApp;
    winApp.buildUI();

    std::cout << "\n";

    MacApp macApp;
    macApp.buildUI();
}
```

**Output:**
```
Khởi tạo UI...
Render [Windows Button]
Click  [Windows style]

Khởi tạo UI...
Render [Mac Button]
Click  [Mac style]