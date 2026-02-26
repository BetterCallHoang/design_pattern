/*Trường hợp 4: Migration dần dần từ hệ thống cũ sang mới
Bài toán: Hệ thống đang dùng LegacyAuthSystem, muốn chuyển sang NewAuthSystem mới mà không down toàn bộ app một lúc.*/
#include <iostream>
#include <string>

class LegacyAuthSystem {
public:
    // Interface cũ
    int authenticate(const std::string& username,
                     const std::string& password) {
        std::cout << "[Legacy] Xác thực: " << username << "\n";
        return (password == "123") ? 1 : 0; // 1=success, 0=fail
    }
};

class NewAuthSystem {
public:
    // Interface mới hoàn toàn khác
    struct AuthResult {
        bool success;
        std::string token;
        std::string errorMsg;
    };
    AuthResult login(const std::string& email,
                     const std::string& hashedPassword) {
        std::cout << "[New] Xác thực: " << email << "\n";
        if (hashedPassword == "hashed_123")
            return {true, "jwt_token_abc", ""};
        return {false, "", "Sai mật khẩu"};
    }
};

// Phải sửa toàn bộ code đang dùng LegacyAuth
// để chuyển sang NewAuth → rủi ro rất cao
class LoginController {
    // Không thể dùng cả hai song song một cách sạch sẽ
    LegacyAuthSystem legacy;
public:
    void login(const std::string& user, const std::string& pass) {
        int result = legacy.authenticate(user, pass);
        // Muốn chuyển sang NewAuth? → sửa hàm này và mọi chỗ gọi nó
        if (result == 1)
            std::cout << "Đăng nhập thành công\n";
        else
            std::cout << "Đăng nhập thất bại\n";
    }
};