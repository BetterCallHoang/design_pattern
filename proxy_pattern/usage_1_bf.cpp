/*Trường hợp 1: Lazy Loading (Virtual Proxy)

Ví dụ: Load ảnh lớn từ disk.*/
#include <iostream>
#include <string>

// [RealSubject]
class Image {
public:
    Image(const std::string& filename) {
        std::cout << "Loading image from disk: " << filename << "\n";
    }

    void display() {
        std::cout << "Displaying image\n";
    }
};

int main() { // [Client]
    Image img("large_photo.jpg"); // luôn load ngay
    img.display();
}