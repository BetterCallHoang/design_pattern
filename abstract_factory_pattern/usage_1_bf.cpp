/*Trường hợp 1: GUI đa nền tảng (Windows / Linux)*/
/*🔴 Vấn đề:

Client phải biết từng class cụ thể

Nếu thêm Mac → sửa code

Không đảm bảo tạo đúng “cặp” sản phẩm*/
#include <iostream>
#include <string>

// Concrete classes
class WinButton {
public:
    void draw() { std::cout << "Draw Windows Button\n"; }
};

class LinuxButton {
public:
    void draw() { std::cout << "Draw Linux Button\n"; }
};

class WinCheckbox {
public:
    void draw() { std::cout << "Draw Windows Checkbox\n"; }
};

class LinuxCheckbox {
public:
    void draw() { std::cout << "Draw Linux Checkbox\n"; }
};

int main() { // [Client]
    std::string os = "Windows";

    if (os == "Windows") {
        WinButton b;
        WinCheckbox c;
        b.draw();
        c.draw();
    } else {
        LinuxButton b;
        LinuxCheckbox c;
        b.draw();
        c.draw();
    }

    return 0;
}