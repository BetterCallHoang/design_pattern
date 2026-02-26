/*Vấn đề

Mỗi thuật toán tự viết toàn bộ pipeline:

1. Load dữ liệu

2. Tiền xử lý

3. Thuật toán chính

4. Hậu xử lý

5. Lưu kết quả

--> Lặp code
--> Dễ sai thứ tự xử lý
--> Khó bảo trì

Nếu thay đổi pipeline → sửa nhiều nơi

Không đảm bảo mọi thuật toán theo cùng một quy chuẩn
*/

#include <iostream>

// ==============================
// Calibration Processor
// ==============================

class CalibrationProcessor {
public:
    void process() {
        loadData();
        preprocess();
        executeCalibration();
        postprocess();
        saveProduct();
    }

private:
    void loadData() {
        std::cout << "Load dữ liệu SAR\n";
    }

    void preprocess() {
        std::cout << "Tiền xử lý dữ liệu\n";
    }

    void executeCalibration() {
        std::cout << "Thực hiện Calibration\n";
    }

    void postprocess() {
        std::cout << "Hậu xử lý\n";
    }

    void saveProduct() {
        std::cout << "Lưu product mới\n";
    }
};

// ==============================
// Speckle Filter Processor
// ==============================

class SpeckleFilterProcessor {
public:
    void process() {
        loadData();
        preprocess();
        executeFilter();
        postprocess();
        saveProduct();
    }

private:
    void loadData() {
        std::cout << "Load dữ liệu SAR\n";
    }

    void preprocess() {
        std::cout << "Tiền xử lý dữ liệu\n";
    }

    void executeFilter() {
        std::cout << "Thực hiện Speckle Filter\n";
    }

    void postprocess() {
        std::cout << "Hậu xử lý\n";
    }

    void saveProduct() {
        std::cout << "Lưu product mới\n";
    }
};

int main() {
    CalibrationProcessor cal;
    cal.process();

    std::cout << "-----------------\n";

    SpeckleFilterProcessor filter;
    filter.process();

    return 0;
}