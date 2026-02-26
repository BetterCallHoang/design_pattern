#include <iostream>
#include <string>

// ===== Subject =====
class IImage { // [Subject]
public:
    virtual ~IImage() = default;
    virtual void display() = 0;
};

// ===== RealSubject =====
class RealImage : public IImage { // [RealSubject]
private:
    std::string filename;
public:
    RealImage(const std::string& file) : filename(file) {
        std::cout << "Loading image from disk: " << filename << "\n";
    }

    void display() override {
        std::cout << "Displaying image\n";
    }
};

// ===== Proxy =====
class ImageProxy : public IImage { // [Proxy]
private:
    std::string filename;
    RealImage* realImage = nullptr;

public:
    ImageProxy(const std::string& file) : filename(file) {}

    void display() override {
        if (!realImage)
            realImage = new RealImage(filename); // lazy load
        realImage->display();
    }
};

int main() { // [Client]
    IImage* img = new ImageProxy("large_photo.jpg");

    std::cout << "App started...\n";
    img->display(); // load xảy ra tại đây

    delete img;
}