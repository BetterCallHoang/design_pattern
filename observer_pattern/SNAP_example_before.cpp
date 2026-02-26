/*Nhược điểm

- Engine phụ thuộc trực tiếp vào UI

- Muốn thêm tính năng mới → phải sửa Engine

- Khó mở rộng*/

#include <iostream>
#include <string>

// Các thành phần giao diện

class ImageView {
public:
    void refresh() {
        std::cout << "ImageView: Cập nhật hiển thị ảnh\n";
    }
};

class ProgressBar {
public:
    void update(int percent) {
        std::cout << "ProgressBar: " << percent << "% hoàn thành\n";
    }
};

class LogSystem {
public:
    void write(const std::string& msg) {
        std::cout << "Log: " << msg << "\n";
    }
};

// Engine xử lý ảnh SAR
class ProcessingEngine {
private:
    ImageView* imageView;
    ProgressBar* progressBar;
    LogSystem* logSystem;

public:
    ProcessingEngine(ImageView* iv,
                     ProgressBar* pb,
                     LogSystem* log)
        : imageView(iv), progressBar(pb), logSystem(log) {}

    void processTile(int percent) {
        std::cout << "Đang xử lý tile...\n";

        // ❌ Gọi trực tiếp từng thành phần
        imageView->refresh();
        progressBar->update(percent);
        logSystem->write("Đã xử lý xong một tile");
    }
};

int main() {
    ImageView iv;
    ProgressBar pb;
    LogSystem log;

    ProcessingEngine engine(&iv, &pb, &log);
    engine.processTile(50);

    return 0;
}