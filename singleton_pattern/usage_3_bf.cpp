/*Trường hợp 3: Hệ thống Log tập trung
Bài toán: Mọi module trong app cần ghi log ra cùng 1 nơi theo đúng thứ tự.*/
#include <iostream>
#include <string>

class Logger {
    std::string module;
public:
    Logger(const std::string& m) : module(m) {}

    void log(const std::string& msg) {
        std::cout << "[" << module << "] " << msg << "\n";
    }
};

class PaymentService {
    Logger logger{"Payment"}; // logger riêng
public:
    void pay() { logger.log("Xử lý thanh toán..."); }
};

class ShippingService {
    Logger logger{"Shipping"}; // logger riêng khác
public:
    void ship() { logger.log("Xử lý vận chuyển..."); }
};

int main() {
    PaymentService payment;
    ShippingService shipping;

    payment.pay();
    shipping.ship();
    // Mỗi service có logger riêng
    // Không thể tập trung: đổi output (file/console/server)
    // phải sửa từng logger một
}