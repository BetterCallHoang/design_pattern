/* Ý tưởng

- Tạo interface chung

- Proxy đại diện cho object thật

- Chỉ load dữ liệu khi cần truy cập pixel*/
#include <iostream>
#include <memory>
#include <string>

// ===============================
// 1. Interface chung
// ===============================

class ISarProduct {
public:
    virtual ~ISarProduct() = default;

    virtual void showMetadata() = 0;
    virtual void getPixel(int x, int y) = 0;
};

// ===============================
// 2. Object thật (rất nặng)
// ===============================

class SarProduct : public ISarProduct {
private:
    std::string filename;

    void loadDataFromDisk() {
        std::cout << "Đang tải toàn bộ dữ liệu ảnh SAR từ đĩa...\n";
        std::cout << "Dữ liệu lớn đã được load vào RAM.\n";
    }

public:
    SarProduct(const std::string& file)
        : filename(file)
    {
        loadDataFromDisk();  // Chỉ load khi được tạo
    }

    void showMetadata() override {
        std::cout << "Metadata của file: " << filename << "\n";
    }

    void getPixel(int x, int y) override {
        std::cout << "Truy cập pixel tại (" << x << ", " << y << ")\n";
    }
};

// ===============================
// 3. Proxy
// ===============================

class SarProductProxy : public ISarProduct {
private:
    std::string filename;

    // Ban đầu chưa có object thật
    std::unique_ptr<SarProduct> realProduct;

    // Chỉ load khi cần
    void ensureLoaded() {
        if (!realProduct) {
            std::cout << "[Proxy] Chưa load dữ liệu. Tiến hành load...\n";
            realProduct = std::make_unique<SarProduct>(filename);
        }
    }

public:
    SarProductProxy(const std::string& file)
        : filename(file)
    {
        // Không load dữ liệu ở đây
    }

    void showMetadata() override {
        // Metadata có thể đọc nhẹ, không cần load toàn bộ
        std::cout << "Metadata (đọc nhanh) của file: "
                  << filename << "\n";
    }

    void getPixel(int x, int y) override {
        // Chỉ load khi thực sự cần pixel
        ensureLoaded();
        realProduct->getPixel(x, y);
    }
};

// ===============================
// 4. Client
// ===============================

int main() {
    std::unique_ptr<ISarProduct> product =
        std::make_unique<SarProductProxy>("sentinel1.dat");

    std::cout << "Chỉ xem metadata:\n";
    product->showMetadata();  // Không load dữ liệu

    std::cout << "\nTruy cập pixel:\n";
    product->getPixel(100, 200);  // Lúc này mới load

    return 0;
}