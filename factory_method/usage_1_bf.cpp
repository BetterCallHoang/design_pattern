/*Trường hợp 1: Không biết trước kiểu đối tượng cần tạo */
#include <iostream>
#include <string>

class DataProcessor {
public:
    void process(const std::string& type, const std::string& filename) {
        // Phải biết hết tất cả các loại ngay tại đây
        // Mỗi lần thêm loại mới → phải sửa hàm này
        if (type == "csv") {
            std::cout << "Đọc file CSV: " << filename << "\n";
            // logic parse CSV...
        } else if (type == "json") {
            std::cout << "Đọc file JSON: " << filename << "\n";
            // logic parse JSON...
        } else if (type == "xml") {
            std::cout << "Đọc file XML: " << filename << "\n";
            // logic parse XML...
        }
        // Thêm "excel"? → phải vào đây sửa tiếp, rất dễ break code cũ
    }
};

int main() {
    DataProcessor dp;
    std::string type;
    std::cout << "Nhập định dạng (csv/json/xml): ";
    std::cin >> type;          // chỉ biết lúc runtime
    dp.process(type, "data.txt");
}