#include <iostream>
#include <string>
#include <memory>

// Interface hệ thống – KHÔNG đổi
class ILogger {
public:
    virtual void log(const std::string& level,
                     const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Thư viện bên thứ 3 – KHÔNG đổi
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

// Adapter – cầu nối giữa ILogger và SentryLogger
class SentryAdapter : public ILogger {
    SentryLogger sentry; // bọc Sentry bên trong

    int levelToSeverity(const std::string& level) const {
        if (level == "DEBUG")   return 0;
        if (level == "INFO")    return 1;
        if (level == "WARNING") return 2;
        if (level == "ERROR")   return 3;
        return 1;
    }

public:
    void log(const std::string& level,
             const std::string& message) override {
        // Chuyển đổi từ interface ILogger sang interface Sentry
        if (level == "ERROR")
            sentry.captureException(message);
        else
            sentry.captureMessage(message, levelToSeverity(level));
    }
};

// Các service chỉ biết ILogger – không biết Sentry tồn tại
class UserService {
    ILogger& logger;
public:
    UserService(ILogger& l) : logger(l) {}

    void createUser(const std::string& name) {
        logger.log("INFO", "Tạo user: " + name);
    }
    void failedLogin(const std::string& name) {
        logger.log("ERROR", "Đăng nhập thất bại: " + name);
    }
};

class OrderService {
    ILogger& logger;
public:
    OrderService(ILogger& l) : logger(l) {}

    void createOrder(int id) {
        logger.log("INFO", "Tạo đơn hàng #" + std::to_string(id));
    }
};

int main() {
    SentryAdapter sentryAdapter;

    UserService  userService(sentryAdapter);
    OrderService orderService(sentryAdapter);

    userService.createUser("Minh");
    userService.failedLogin("Hacker");
    orderService.createOrder(42);

    // Ngày mai đổi sang Datadog?
    // Chỉ cần viết DatadogAdapter và thay 1 dòng ở đây
    // Toàn bộ UserService, OrderService không cần sửa
}
```

**Output:**
```
[Sentry] severity=1 | Tạo user: Minh
[Sentry][Exception] Đăng nhập thất bại: Hacker
[Sentry] severity=1 | Tạo đơn hàng #42