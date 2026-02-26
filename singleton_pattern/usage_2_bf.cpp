/*Trường hợp 2: Quản lý cấu hình toàn cục
Bài toán: Config của app (API key, timeout, môi trường...) cần đọc từ file 1 lần và dùng ở nhiều nơi.*/
#include <iostream>
#include <string>
#include <map>

class Config {
    std::map<std::string, std::string> settings;
public:
    Config() {
        // Giả lập đọc file config – thực tế rất tốn I/O
        std::cout << "[Config] Đọc file config...\n";
        settings["api_url"]  = "https://api.example.com";
        settings["timeout"]  = "30";
        settings["env"]      = "production";
    }

    std::string get(const std::string& key) {
        return settings.count(key) ? settings.at(key) : "";
    }
};

class ApiService {
    Config config; // đọc file lần 1
public:
    void call() {
        std::cout << "Gọi API: " << config.get("api_url") << "\n";
    }
};

class AuthService {
    Config config; // đọc file lần 2 – thừa!
public:
    void login() {
        std::cout << "Timeout: " << config.get("timeout") << "s\n";
    }
};

int main() {
    ApiService  api;  // đọc config lần 1
    AuthService auth; // đọc config lần 2

    api.call();
    auth.login();
    // Nếu ai đó sửa config trong ApiService thì AuthService không biết
}
```

**Output:**
```
[Config] Đọc file config...
[Config] Đọc file config...
Gọi API: https://api.example.com
Timeout: 30s