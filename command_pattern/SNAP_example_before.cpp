/* Vấn đề

- UI gọi trực tiếp zoom(), rotate()

- Không lưu được lịch sử

- Không hỗ trợ Undo/Redo*/

#include <iostream>

// Lớp hiển thị ảnh
class ImageViewport {
private:
    double scale = 1.0;
    double rotationAngle = 0.0;

public:
    void zoom(double factor) {
        scale *= factor;
        std::cout << "Zoom: scale = " << scale << "\n";
    }

    void rotate(double angle) {
        rotationAngle += angle;
        std::cout << "Rotate: angle = " << rotationAngle << "\n";
    }
};

int main() {
    ImageViewport viewport;

    // UI gọi trực tiếp
    viewport.zoom(1.2);
    viewport.rotate(90);

    // ❌ Không thể undo
    return 0;
}