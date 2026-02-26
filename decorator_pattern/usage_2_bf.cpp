/*Kết hợp nhiều tính năng theo cách tự do, linh hoạt*/
#include <iostream>
#include <string>
#include <algorithm>

class TextProcessor {
public:
    // Dùng flag để bật tắt từng tính năng
    bool enableUppercase  = false;
    bool enableBrackets   = false;
    bool enablePrefix     = false;

    std::string process(std::string text) {
        // Thứ tự xử lý cố định, không thể thay đổi
        if (enableUppercase)
            std::transform(text.begin(), text.end(), text.begin(), ::toupper);

        if (enableBrackets)
            text = "[" + text + "]";

        if (enablePrefix)
            text = "INFO: " + text;

        // Thêm tính năng mới (trim, encrypt...) → phải vào đây thêm flag + if
        // Thứ tự luôn cố định: uppercase → brackets → prefix
        // Không thể đổi thành prefix → uppercase → brackets
        return text;
    }
};

int main() {
    TextProcessor tp;
    tp.enableUppercase = true;
    tp.enablePrefix    = true;

    std::cout << tp.process("hello world") << "\n";
    // Luôn ra: INFO: HELLO WORLD
    // Không thể ra: HELLO WORLD với prefix ở sau
}