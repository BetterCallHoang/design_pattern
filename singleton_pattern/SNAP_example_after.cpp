/*
- Chỉ có 1 Logger duy nhất

- Mọi nơi dùng chung*/

#include <iostream>
#include <string>

// Logger sử dụng Singleton Pattern
class Logger {
public:
    // Xóa constructor public để không cho tạo từ bên ngoài
    Logger(const Logger&) = delete;            // Cấm copy
    Logger& operator=(const Logger&) = delete; // Cấm gán

    // Hàm truy cập duy nhất đến instance
    static Logger& getInstance() {
        // Static local variable
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

private:
    // Constructor private để không ai tạo được trực tiếp
    Logger() {
        std::cout << "Logger được tạo duy nhất một lần\n";
    }
};

// Module xử lý ảnh
class ImageProcessor {
public:
    void process() {
        // Lấy logger chung
        Logger::getInstance().log("Bắt đầu xử lý ảnh");
    }
};

// Module hiệu chỉnh
class CalibrationModule {
public:
    void calibrate() {
        // Dùng cùng một logger
        Logger::getInstance().log("Bắt đầu hiệu chỉnh");
    }
};

int main() {
    ImageProcessor p;
    CalibrationModule c;

    p.process();
    c.calibrate();

    return 0;
}