/* Mở rộng không sửa code cũ */

#include <iostream>
#include <string>

class NotificationService {
public:
    // Mỗi lần thêm kênh mới → phải vào đây sửa
    void send(const std::string& channel, const std::string& msg) {
        if (channel == "email") {
            std::cout << "[Email] Gửi: " << msg << "\n";
        } else if (channel == "sms") {
            std::cout << "[SMS] Gửi: " << msg << "\n";
        }
        // Thêm "push"? → sửa thẳng vào class này
        // Nếu class này đang chạy production → rất nguy hiểm
    }
};