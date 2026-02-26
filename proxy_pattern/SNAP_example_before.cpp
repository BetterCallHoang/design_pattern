/*Vấn đề

- Object thật load dữ liệu ngay khi được tạo

--> Tốn RAM dù chưa cần truy cập pixel

--> Thời gian khởi động lâu
*/
#include <iostream>
#include <string>

// Lớp ảnh SAR thật (nặng)
class SarProduct {
private:
    std::string filename;

    void loadDataFromDisk() {
        std::cout << "Đang tải toàn bộ dữ liệu ảnh SAR từ đĩa...\n";
        std::cout << "Dữ liệu lớn đã được load vào RAM.\n";
    }

public:
    // Constructor load dữ liệu ngay lập tức
    SarProduct(const std::string& file)
        : filename(file)
    {
        loadDataFromDisk();  // Luôn load dù chưa cần
    }

    void showMetadata() {
        std::cout << "Metadata của file: " << filename << "\n";
    }

    void getPixel(int x, int y) {
        std::cout << "Truy cập pixel tại (" << x << ", " << y << ")\n";
    }
};
// Client 
int main() {
    // Tạo object -> dữ liệu load ngay
    SarProduct product("sentinel1.dat");

    std::cout << "Chỉ xem metadata:\n";
    product.showMetadata();

    return 0;
}