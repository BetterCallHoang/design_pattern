#include <iostream>
#include <string>
#include <memory>

// Interface chuẩn của hệ thống
class IAuthService {
public:
    struct AuthResult {
        bool        success;
        std::string token;
        std::string errorMsg;
    };
    virtual AuthResult login(const std::string& user,
                             const std::string& pass) = 0;
    virtual ~IAuthService() = default;
};

// Hệ thống cũ – KHÔNG sửa
class LegacyAuthSystem {
public:
    int authenticate(const std::string& username,
                     const std::string& password) {
        std::cout << "[Legacy] Xác thực: " << username << "\n";
        return (password == "123") ? 1 : 0;
    }
};

// Hệ thống mới
class NewAuthSystem {
public:
    IAuthService::AuthResult login(const std::string& email,
                                   const std::string& hashedPassword) {
        std::cout << "[New] Xác thực: " << email << "\n";
        if (hashedPassword == "hashed_123")
            return {true, "jwt_token_abc", ""};
        return {false, "", "Sai mật khẩu"};
    }
};

// Adapter cho Legacy – dùng trong giai đoạn chuyển tiếp
class LegacyAuthAdapter : public IAuthService {
    LegacyAuthSystem legacy;
public:
    AuthResult login(const std::string& user,
                     const std::string& pass) override {
        int result = legacy.authenticate(user, pass);
        if (result == 1)
            return {true, "legacy_session_token", ""};
        return {false, "", "Xác thực thất bại"};
    }
};

// Adapter cho New
class NewAuthAdapter : public IAuthService {
    NewAuthSystem newAuth;

    std::string hashPassword(const std::string& pass) const {
        return "hashed_" + pass; // thực tế dùng bcrypt/sha256
    }
public:
    AuthResult login(const std::string& user,
                     const std::string& pass) override {
        return newAuth.login(user, hashPassword(pass));
    }
};

// Controller chỉ biết IAuthService – không biết Legacy hay New
class LoginController {
    IAuthService& authService;
public:
    LoginController(IAuthService& auth) : authService(auth) {}

    void login(const std::string& user, const std::string& pass) {
        auto result = authService.login(user, pass);
        if (result.success)
            std::cout << "Đăng nhập thành công! Token: "
                      << result.token << "\n";
        else
            std::cout << "Đăng nhập thất bại: "
                      << result.errorMsg << "\n";
    }
};

int main() {
    std::cout << "=== Giai đoạn 1: Dùng Legacy (chưa migrate) ===\n";
    LegacyAuthAdapter legacyAdapter;
    LoginController   controller1(legacyAdapter);
    controller1.login("minh", "123");

    std::cout << "\n=== Giai đoạn 2: Đã migrate sang New ===\n";
    NewAuthAdapter newAdapter;
    LoginController controller2(newAdapter);
    controller2.login("minh@example.com", "123");

    // LoginController không đổi một dòng nào
    // Chỉ swap adapter là xong
}
```

**Output:**
```
=== Giai đoạn 1: Dùng Legacy (chưa migrate) ===
[Legacy] Xác thực: minh
Đăng nhập thành công! Token: legacy_session_token

=== Giai đoạn 2: Đã migrate sang New ===
[New] Xác thực: minh@example.com
Đăng nhập thành công! Token: jwt_token_abc