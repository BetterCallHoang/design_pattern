#include <iostream>
#include <string>
#include <queue>

class PrinterDriver {
    std::queue<std::string> printQueue;
    int jobCounter = 0;

    PrinterDriver() {
        std::cout << "[Printer] Khởi tạo driver máy in\n\n";
    }

public:
    PrinterDriver(const PrinterDriver&)            = delete;
    PrinterDriver& operator=(const PrinterDriver&) = delete;

    static PrinterDriver& getInstance() {
        static PrinterDriver instance;
        return instance;
    }

    void addJob(const std::string& doc) {
        std::string job = "Job#" + std::to_string(++jobCounter) + ": " + doc;
        printQueue.push(job);
        std::cout << "[Printer] Thêm vào hàng đợi: " << job << "\n";
    }

    void processQueue() {
        std::cout << "\n[Printer] Bắt đầu in...\n";
        while (!printQueue.empty()) {
            std::cout << "[Printer] Đang in: " << printQueue.front() << "\n";
            printQueue.pop();
        }
        std::cout << "[Printer] Hoàn tất!\n";
    }
};

// Các module khác nhau đều gửi vào cùng 1 hàng đợi
class OfficeApp {
public:
    void print(const std::string& doc) {
        PrinterDriver::getInstance().addJob(doc);
    }
};

class BrowserApp {
public:
    void printPage(const std::string& page) {
        PrinterDriver::getInstance().addJob(page);
    }
};

int main() {
    OfficeApp office;
    BrowserApp browser;

    office.print("Báo cáo tháng 1.pdf");
    browser.printPage("Trang web hóa đơn");
    office.print("Hợp đồng.docx");

    // Tất cả vào đúng 1 hàng đợi, in theo thứ tự
    PrinterDriver::getInstance().processQueue();
}
```

**Output:**
```
[Printer] Khởi tạo driver máy in

[Printer] Thêm vào hàng đợi: Job#1: Báo cáo tháng 1.pdf
[Printer] Thêm vào hàng đợi: Job#2: Trang web hóa đơn
[Printer] Thêm vào hàng đợi: Job#3: Hợp đồng.docx

[Printer] Bắt đầu in...
[Printer] Đang in: Job#1: Báo cáo tháng 1.pdf
[Printer] Đang in: Job#2: Trang web hóa đơn
[Printer] Đang in: Job#3: Hợp đồng.docx
[Printer] Hoàn tất!