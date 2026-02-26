#include <iostream>
#include <string>

struct User { std::string name, email; };

// Các handler riêng lẻ
class EmailSender {
public:
    void sendWelcome(const User& u) {
        std::cout << "[Email] Gửi email chào mừng tới " << u.email << "\n";
    }
};

class ActivityLogger {
public:
    void logNewUser(const User& u) {
        std::cout << "[Log] Ghi nhận user mới: " << u.name << "\n";
    }
};

class RewardService {
public:
    void grantSignupBonus(const User& u) {
        std::cout << "[Reward] Tặng 100 điểm cho " << u.name << "\n";
    }
};

class UserService {
    // Phải giữ tất cả dependency – gắn cứng hoàn toàn
    EmailSender emailSender;
    ActivityLogger logger;
    RewardService rewardService;

public:
    void createUser(const std::string& name, const std::string& email) {
        User user{name, email};
        std::cout << "Tạo user: " << name << "\n\n";

        // Mỗi tác vụ phát sinh sau này → phải vào đây thêm
        // UserService đang làm QUÁ NHIỀU việc – vi phạm Single Responsibility
        emailSender.sendWelcome(user);
        logger.logNewUser(user);
        rewardService.grantSignupBonus(user);

        // Tương lai cần thêm: gửi SMS, thông báo admin, sync CRM...
        // → tiếp tục vào đây nhét thêm, class ngày càng nặng
    }
};

int main() {
    UserService service;
    service.createUser("Minh", "minh@example.com");
}