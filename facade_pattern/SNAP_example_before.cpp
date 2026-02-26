/*
- Người dùng phải biết đúng thứ tự thao tác ảnh, trong khi chỉ muốn tạo "Ảnh giao thoa đồ"
*/


#include <iostream>

// Các hệ thống con (Subsystem)

class Coregistration {
public:
    void execute() {
        std::cout << "Đồng đăng ký ảnh...\n";
    }
};

class OrbitCorrection {
public:
    void execute() {
        std::cout << "Hiệu chỉnh quỹ đạo...\n";
    }
};

class FlatEarthRemoval {
public:
    void execute() {
        std::cout << "Loại bỏ pha mặt phẳng...\n";
    }
};

class PhaseFiltering {
public:
    void execute() {
        std::cout << "Lọc pha...\n";
    }
};

class Multilook {
public:
    void execute() {
        std::cout << "Thực hiện multilook...\n";
    }
};

int main() {
    // Người dùng phải biết toàn bộ thứ tự xử lý
    Coregistration coreg;
    OrbitCorrection orbit;
    FlatEarthRemoval flat;
    PhaseFiltering filter;
    Multilook multilook;

    coreg.execute();
    orbit.execute();
    flat.execute();
    filter.execute();
    multilook.execute();

    return 0;
}