/*3. Khi observer có thể thay đổi linh hoạt lúc runtime
Subscribe/unsubscribe bất kỳ lúc nào – không cần compile lại.
Ví dụ: Hệ thống log – bật/tắt ghi log ra file hoặc console tùy môi trường.*/ 
#include <iostream>
#include <vector>
#include <string>

class ILogger {
public:
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = default;
};
// Oserverable
class LogManager {
    std::vector<ILogger*> loggers;
public:
    void addLogger(ILogger* l)    { loggers.push_back(l); }
    void removeLogger(ILogger* l) {
        loggers.erase(
            std::remove(loggers.begin(), loggers.end(), l),
            loggers.end()
        );
    }
    void log(const std::string& msg) {
        for (auto* l : loggers) l->log(msg);
    }
};
// Concrete Observer 
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        std::cout << "[Console] " << msg << "\n";
    }
};

class FileLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        // thực tế sẽ ghi file, ở đây in để minh họa
        std::cout << "[File]    " << msg << "\n";
    }
};

int main() {
    LogManager manager; //Observable 
    ConsoleLogger console; 
    FileLogger file;

    // Môi trường dev: log cả hai
    manager.addLogger(&console);
    manager.addLogger(&file);
    manager.log("App khởi động");

    std::cout << "\n-- Chuyển sang production: tắt console --\n\n";

    // Môi trường production: chỉ log file
    manager.removeLogger(&console);
    manager.log("User đăng nhập");
}
```

**Output:**
```
[Console] App khởi động
[File]    App khởi động

-- Chuyển sang production: tắt console --

[File]    User đăng nhập