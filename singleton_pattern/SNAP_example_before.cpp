/*Vấn đề:

- Mỗi module tự tạo Logger

- Có nhiều instance khác nhau

- Log không tập trung
--> Có thể tạo ra nhiều file log */
#include <iostream>
#include <string>

// Lớp Logger bình thường
class Logger {
public:
    Logger() {
        std::cout << "Logger được tạo\n";
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// Module xử lý ảnh
class ImageProcessor {
private:
    Logger logger;  // Mỗi module có logger riêng

public:
    void process() {
        logger.log("Bắt đầu xử lý ảnh");
    }
};

// Module hiệu chỉnh
class CalibrationModule {
private:
    Logger logger;  // Lại tạo thêm một logger khác

public:
    void calibrate() {
        logger.log("Bắt đầu hiệu chỉnh");
    }
};

int main() {
    ImageProcessor p;
    CalibrationModule c;

    p.process();
    c.calibrate();

    return 0;
}