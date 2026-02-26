/*Trường hợp 1: Tích hợp thư viện bên thứ ba không tương thích interface
Bài toán: App đang dùng interface ILogger của riêng mình, nhưng muốn tích hợp thư viện log bên ngoài (SentryLogger) mà không sửa code cũ*/
#include <iostream>
#include <string>

// Interface hệ thống đang dùng
class ILogger {
public:
    virtual void log(const std::string& level,
                     const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Thư viện bên thứ 3 – không thể sửa
class SentryLogger {
public:
    void captureMessage(const std::string& msg, int severity) {
        std::cout << "[Sentry] severity=" << severity
                  << " | " << msg << "\n";
    }
    void captureException(const std::string& error) {
        std::cout << "[Sentry][Exception] " << error << "\n";
    }
};

// Để dùng SentryLogger, buộc phải sửa toàn bộ code cũ
// từ logger->log("ERROR", msg) thành sentry.captureMessage(msg, 3)
// → phải tìm và sửa hàng trăm chỗ trong codebase
class UserService {
    SentryLogger sentry; // gắn cứng với Sentry
public:
    void createUser(const std::string& name) {
        // Không dùng interface chung được nữa
        sentry.captureMessage("Tạo user: " + name, 1);
    }
};

class OrderService {
    SentryLogger sentry; // lại gắn cứng Sentry ở chỗ khác
public:
    void createOrder(int id) {
        sentry.captureMessage("Tạo đơn: " + std::to_string(id), 1);
    }
};

int main() {
    UserService user;
    OrderService order;
    user.createUser("Minh");
    order.createOrder(42);
    // Ngày mai muốn đổi từ Sentry sang Datadog?
    // Lại phải tìm và sửa từng chỗ một
}