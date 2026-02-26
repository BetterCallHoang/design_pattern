/*4. Khi một thay đổi kéo theo nhiều thay đổi khác mà bạn chưa biết trước
Ví dụ: Form đăng ký user – khi tạo user xong, hệ thống cần gửi email, lưu log, tặng điểm... và tương lai có thể cần thêm nhiều tác vụ nữa.*/
#include <iostream>
#include <vector>
#include <string>

struct User { std::string name, email; };

class IUserEventHandler {
public:
    virtual void onUserCreated(const User& user) = 0;
    virtual ~IUserEventHandler() = default;
};

class UserService {
    std::vector<IUserEventHandler*> handlers;
public:
    void addHandler(IUserEventHandler* h) { handlers.push_back(h); }

    void createUser(const std::string& name, const std::string& email) {
        User user{name, email};
        std::cout << "Tạo user: " << name << "\n\n";

        // Không cần biết sẽ có bao nhiêu handler
        for (auto* h : handlers)
            h->onUserCreated(user);
    }
};

class EmailHandler : public IUserEventHandler {
public:
    void onUserCreated(const User& u) override {
        std::cout << "[Email] Gửi email chào mừng tới " << u.email << "\n";
    }
};

class LogHandler : public IUserEventHandler {
public:
    void onUserCreated(const User& u) override {
        std::cout << "[Log] Ghi nhận user mới: " << u.name << "\n";
    }
};

// Thêm sau này mà không sửa UserService
class RewardHandler : public IUserEventHandler {
public:
    void onUserCreated(const User& u) override {
        std::cout << "[Reward] Tặng 100 điểm cho " << u.name << "\n";
    }
};

int main() {
    UserService service;

    EmailHandler  emailHandler;
    LogHandler    logHandler;
    RewardHandler rewardHandler;

    service.addHandler(&emailHandler);
    service.addHandler(&logHandler);
    service.addHandler(&rewardHandler); // thêm mới, không sửa UserService

    service.createUser("Minh", "minh@example.com");
}
```

**Output:**
```
Tạo user: Minh

[Email] Gửi email chào mừng tới minh@example.com
[Log] Ghi nhận user mới: Minh
[Reward] Tặng 100 điểm cho Minh