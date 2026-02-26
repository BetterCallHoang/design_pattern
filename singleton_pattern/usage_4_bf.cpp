/*Trường hợp 4: Quản lý trạng thái thiết bị/phần cứng
Bài toán: Driver máy in – chỉ được có 1 instance quản lý hàng đợi in, nếu có nhiều instance sẽ gây xung đột lệnh.*/
#include <iostream>
#include <string>
#include <queue>

class PrinterDriver {
    std::queue<std::string> printQueue;
public:
    PrinterDriver() {
        std::cout << "[Printer] Khởi tạo driver máy in\n";
    }

    void addJob(const std::string& doc) {
        printQueue.push(doc);
        std::cout << "[Printer] Thêm lệnh in: " << doc << "\n";
    }

    void processQueue() {
        while (!printQueue.empty()) {
            std::cout << "[Printer] Đang in: " << printQueue.front() << "\n";
            printQueue.pop();
        }
    }
};

int main() {
    PrinterDriver driver1; // App tạo driver 1
    PrinterDriver driver2; // Module khác tạo driver 2 riêng

    driver1.addJob("Báo cáo tháng 1.pdf");
    driver2.addJob("Hợp đồng.docx");      // vào queue khác!

    driver1.processQueue(); // chỉ in file của driver1
    driver2.processQueue(); // chỉ in file của driver2
    // Nếu cả 2 cùng gửi lệnh xuống máy in thật → xung đột!
}