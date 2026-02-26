#include <iostream>
#include <memory>
#include <string>

// IProduct
class Notification {
public:
    virtual void send(const std::string& msg) const = 0;
    virtual ~Notification() = default;
};
// Concrete product 
class EmailNotification : public Notification {
public:
    void send(const std::string& msg) const override {
        std::cout << "[Email] Gửi: " << msg << "\n";
    }
};
// Concrete product
class SMSNotification : public Notification {
public:
    void send(const std::string& msg) const override {
        std::cout << "[SMS] Gửi: " << msg << "\n";
    }
};

// Thêm mới sau này → KHÔNG sửa gì ở trên
class PushNotification : public Notification {
public:
    void send(const std::string& msg) const override {
        std::cout << "[Push] Gửi: " << msg << "\n";
    }
};

// Creator / IFactory 
class NotificationService {
public:
// Factory method 
    virtual std::unique_ptr<Notification> createNotification() const = 0;

    void notify(const std::string& msg) const {
        auto n = createNotification();
        n->send(msg);
    }
    virtual ~NotificationService() = default;
};
// Concrete factory 
class EmailService : public NotificationService {
    std::unique_ptr<Notification> createNotification() const override {
        return std::make_unique<EmailNotification>();
    }
};
class SMSService : public NotificationService {
    std::unique_ptr<Notification> createNotification() const override {
        return std::make_unique<SMSNotification>();
    }
};
// Thêm kênh mới: chỉ thêm class này, không đụng EmailService/SMSService
class PushService : public NotificationService {
    std::unique_ptr<Notification> createNotification() const override {
        return std::make_unique<PushNotification>();
    }
};

int main() {
    EmailService email;
    SMSService   sms;
    PushService  push; // thêm mới, hoàn toàn độc lập

    email.notify("Đơn hàng đã xác nhận!");
    sms.notify("Mã OTP: 123456");
    push.notify("Có tin nhắn mới!");
}