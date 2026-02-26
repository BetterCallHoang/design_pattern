/*Trường hợp 1: Tài nguyên chia sẻ chỉ nên có 1 instance
Bài toán: Kết nối database – tạo nhiều connection pool sẽ lãng phí tài nguyên và gây xung đột.*/

#include <iostream>
#include <string>

class DatabaseConnection {
    std::string connStr;
public:
    DatabaseConnection(const std::string& str) : connStr(str) {
        // Mỗi lần khởi tạo = tốn chi phí kết nối thật
        std::cout << "[DB] Mở kết nối mới tới: " << connStr << "\n";
    }

    void query(const std::string& sql) {
        std::cout << "[DB] Thực thi: " << sql << "\n";
    }

    ~DatabaseConnection() {
        std::cout << "[DB] Đóng kết nối\n";
    }
};

class UserRepository {
    DatabaseConnection db; // tự tạo connection riêng
public:
    UserRepository() : db("postgresql://localhost/mydb") {}
    void findUser(int id) { db.query("SELECT * FROM users WHERE id=" + std::to_string(id)); }
};

class OrderRepository {
    DatabaseConnection db; // lại tạo thêm 1 connection nữa
public:
    OrderRepository() : db("postgresql://localhost/mydb") {}
    void findOrder(int id) { db.query("SELECT * FROM orders WHERE id=" + std::to_string(id)); }
};

int main() {
    UserRepository  userRepo;  // mở connection 1
    OrderRepository orderRepo; // mở connection 2 – lãng phí!

    userRepo.findUser(1);
    orderRepo.findOrder(1);
    // 2 connection cho cùng 1 database → lãng phí, có thể gây conflict
}
```

**Output:**
```
[DB] Mở kết nối mới tới: postgresql://localhost/mydb
[DB] Mở kết nối mới tới: postgresql://localhost/mydb
[DB] Thực thi: SELECT * FROM users WHERE id=1
[DB] Thực thi: SELECT * FROM orders WHERE id=1
[DB] Đóng kết nối
[DB] Đóng kết nối