#include <iostream>
#include <string>

class ConsoleLogger {
public:
    void log(const std::string& msg) {
        std::cout << "[Console] " << msg << "\n";
    }
};

class FileLogger {
public:
    void log(const std::string& msg) {
        std::cout << "[File]    " << msg << "\n";
    }
};

class LogManager {
    ConsoleLogger console;
    FileLogger file;

    bool useConsole = true;  // Phải dùng flag thủ công để "giả lập" bật/tắt
    bool useFile    = true;

public:
    // Không có cách nào thêm logger mới mà không sửa class này
    void setUseConsole(bool v) { useConsole = v; }
    void setUseFile(bool v)    { useFile = v; }

    void log(const std::string& msg) {
        if (useConsole) console.log(msg);
        if (useFile)    file.log(msg);
        // Thêm DatabaseLogger? → thêm field, thêm flag, thêm if → class phình to
    }
};

int main() {
    LogManager manager;

    manager.log("App khởi động");

    std::cout << "\n-- Chuyển sang production: tắt console --\n\n";

    manager.setUseConsole(false); // "tắt" bằng flag, không thực sự linh hoạt
    manager.log("User đăng nhập");
}