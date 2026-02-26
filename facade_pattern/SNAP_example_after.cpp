#include <iostream>

// =======================
// Các hệ thống con
// =======================

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

// =======================
// Facade
// =======================

class InterferogramProcessor {
private:
    Coregistration coreg;
    OrbitCorrection orbit;
    FlatEarthRemoval flat;
    PhaseFiltering filter;
    Multilook multilook;

public:
    // Hàm duy nhất mà người dùng cần gọi
    void process() {
        std::cout << "Bắt đầu tạo Interferogram...\n";

        coreg.execute();
        orbit.execute();
        flat.execute();
        filter.execute();
        multilook.execute();

        std::cout << "Hoàn thành Interferogram.\n";
    }
};

// =======================
// Client
// =======================

int main() {
    InterferogramProcessor processor;

    // Người dùng chỉ cần gọi một hàm
    processor.process();

    return 0;
}