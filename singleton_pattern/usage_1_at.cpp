#include <iostream>
#include <string>
#include <mutex>

class DatabaseConnection {
    std::string connStr;

    // Constructor private – không ai tạo trực tiếp được
    DatabaseConnection(const std::string& str) : connStr(str) {
        std::cout << "[DB] Mở kết nối tới: " << connStr << "\n";
    }

public:
    // Xóa copy constructor và assignment để tránh nhân bản
    DatabaseConnection(const DatabaseConnection&)            = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    static DatabaseConnection& getInstance() {
        // Thread-safe trong C++11 trở đi: static local init chỉ chạy 1 lần
        static DatabaseConnection instance("postgresql://localhost/mydb");
        return instance;
    }

    void query(const std::string& sql) {
        std::cout << "[DB] Thực thi: " << sql << "\n";
    }
};

class UserRepository {
public:
    void findUser(int id) {
        // Lấy instance dùng chung – không tạo mới
        DatabaseConnection::getInstance()
            .query("SELECT * FROM users WHERE id=" + std::to_string(id));
    }
};

class OrderRepository {
public:
    void findOrder(int id) {
        // Cùng instance với UserRepository
        DatabaseConnection::getInstance()
            .query("SELECT * FROM orders WHERE id=" + std::to_string(id));
    }
};

int main() {
    UserRepository  userRepo;
    OrderRepository orderRepo;

    userRepo.findUser(1);    // dùng connection duy nhất
    orderRepo.findOrder(1);  // vẫn dùng connection đó
}
```

**Output:**
```
[DB] Mở kết nối tới: postgresql://localhost/mydb
[DB] Thực thi: SELECT * FROM users WHERE id=1
[DB] Thực thi: SELECT * FROM orders WHERE id=1