#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

class Logger {
    std::vector<std::string> history;

    Logger() { std::cout << "[Logger] Khởi tạo hệ thống log\n\n"; }

    std::string timestamp() const {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::string ts = std::ctime(&time);
        ts.pop_back(); // bỏ '\n'
        return ts;
    }

public:
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& level, const std::string& module,
             const std::string& msg) {
        std::string entry = "[" + level + "][" + module + "] " + msg;
        history.push_back(entry);
        std::cout << entry << "\n";
    }

    void printHistory() const {
        std::cout << "\n=== Lịch sử log ===\n";
        for (auto& entry : history)
            std::cout << entry << "\n";
    }
};

class PaymentService {
public:
    void pay(double amount) {
        Logger::getInstance().log("INFO", "Payment",
            "Thanh toán " + std::to_string(amount) + " VND");
    }
    void fail() {
        Logger::getInstance().log("ERROR", "Payment", "Thanh toán thất bại!");
    }
};

class ShippingService {
public:
    void ship(const std::string& address) {
        Logger::getInstance().log("INFO", "Shipping",
            "Giao hàng tới: " + address);
    }
};

int main() {
    PaymentService  payment;
    ShippingService shipping;

    payment.pay(500000);
    shipping.ship("123 Lê Lợi, HCM");
    payment.fail();

    // Tất cả log tập trung – in lịch sử ở bất kỳ đâu
    Logger::getInstance().printHistory();
}
```

**Output:**
```
[Logger] Khởi tạo hệ thống log

[INFO][Payment] Thanh toán 500000.000000 VND
[INFO][Shipping] Giao hàng tới: 123 Lê Lợi, HCM
[ERROR][Payment] Thanh toán thất bại!

=== Lịch sử log ===
[INFO][Payment] Thanh toán 500000.000000 VND
[INFO][Shipping] Giao hàng tới: 123 Lê Lợi, HCM
[ERROR][Payment] Thanh toán thất bại!