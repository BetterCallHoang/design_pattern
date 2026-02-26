#include <iostream>

// =====================================
// 1️⃣ Abstract Class - Template Method
// =====================================

class SarProcessor {
public:
    // Template Method - khung xử lý cố định
    void process() {
        loadData();
        preprocess();
        executeAlgorithm();  // Bước khác nhau
        postprocess();
        saveProduct();
    }

    virtual ~SarProcessor() = default;

protected:
    void loadData() {
        std::cout << "Load dữ liệu SAR\n";
    }

    void preprocess() {
        std::cout << "Tiền xử lý dữ liệu\n";
    }

    void postprocess() {
        std::cout << "Hậu xử lý\n";
    }

    void saveProduct() {
        std::cout << "Lưu product mới\n";
    }

    // Bước bắt buộc lớp con phải định nghĩa
    virtual void executeAlgorithm() = 0;
};

// =====================================
// 2️⃣ Concrete Class - Calibration
// =====================================

class CalibrationProcessor : public SarProcessor {
protected:
    void executeAlgorithm() override {
        std::cout << "Thực hiện Calibration\n";
    }
};

// =====================================
// 3️⃣ Concrete Class - Speckle Filter
// =====================================

class SpeckleFilterProcessor : public SarProcessor {
protected:
    void executeAlgorithm() override {
        std::cout << "Thực hiện Speckle Filter\n";
    }
};

// =====================================
// 4️⃣ Client
// =====================================

int main() {
    SarProcessor* processor1 = new CalibrationProcessor();
    processor1->process();

    std::cout << "-----------------\n";

    SarProcessor* processor2 = new SpeckleFilterProcessor();
    processor2->process();

    delete processor1;
    delete processor2;

    return 0;
}