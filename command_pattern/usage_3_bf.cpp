/*Trường hợp 3: Tách biệt người gửi lệnh và người thực thi
Bài toán: Remote control điều khiển thiết bị thông minh – nút bấm không nên biết thiết bị cụ thể là gì.*/
#include <iostream>

class Light {
public:
    void on()  { std::cout << "Đèn bật\n"; }
    void off() { std::cout << "Đèn tắt\n"; }
};

class Fan {
public:
    void on()  { std::cout << "Quạt bật\n"; }
    void off() { std::cout << "Quạt tắt\n"; }
};

// Remote phải biết từng thiết bị cụ thể
// Thêm thiết bị mới (TV, máy lạnh) → phải sửa Remote
class Remote {
    Light light;
    Fan   fan;
public:
    void pressButton(const std::string& device, const std::string& action) {
        if (device == "light") {
            if (action == "on")  light.on();
            else                 light.off();
        } else if (device == "fan") {
            if (action == "on")  fan.on();
            else                 fan.off();
        }
        // Thêm TV → vào đây thêm else if tiếp
    }
};

int main() {
    Remote remote;
    remote.pressButton("light", "on");
    remote.pressButton("fan",   "on");
    remote.pressButton("light", "off");
}