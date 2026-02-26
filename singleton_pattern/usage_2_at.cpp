#include <iostream>
#include <string>
#include <map>

class Config {
    std::map<std::string, std::string> settings;

    Config() {
        std::cout << "[Config] Đọc file config...\n";
        settings["api_url"] = "https://api.example.com";
        settings["timeout"] = "30";
        settings["env"]     = "production";
    }

public:
    Config(const Config&)            = delete;
    Config& operator=(const Config&) = delete;

    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    std::string get(const std::string& key) const {
        return settings.count(key) ? settings.at(key) : "";
    }

    void set(const std::string& key, const std::string& value) {
        settings[key] = value;
    }
};

class ApiService {
public:
    void call() {
        // Tất cả đều dùng chung 1 config
        std::cout << "Gọi API: " << Config::getInstance().get("api_url") << "\n";
    }
};

class AuthService {
public:
    void login() {
        std::cout << "Timeout: " << Config::getInstance().get("timeout") << "s\n";
        std::cout << "Môi trường: " << Config::getInstance().get("env") << "\n";
    }
};

int main() {
    ApiService  api;
    AuthService auth;

    api.call();
    auth.login();

    std::cout << "\n-- Thay đổi config lúc runtime --\n";
    Config::getInstance().set("env", "staging");

    // Tất cả service đều thấy thay đổi ngay lập tức
    auth.login();
}
```

**Output:**
```
[Config] Đọc file config...
Gọi API: https://api.example.com
Timeout: 30s
Môi trường: production

-- Thay đổi config lúc runtime --
Timeout: 30s
Môi trường: staging