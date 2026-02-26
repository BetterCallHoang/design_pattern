/*Thêm behavior lúc runtime tùy theo điều kiện*/
#include <iostream>
#include <string>

class HttpClient {
public:
    bool enableLogging = false;
    bool enableAuth    = false;
    bool enableCache   = false;

    std::string send(const std::string& url) {
        // Logic xử lý bị trộn lẫn trong 1 hàm
        if (enableLogging)
            std::cout << "[Log] Gửi request tới: " << url << "\n";

        if (enableAuth)
            std::cout << "[Auth] Đính kèm token\n";

        if (enableCache) {
            std::cout << "[Cache] Kiểm tra cache...\n";
            // Không có cache giả lập
        }

        std::cout << "[HTTP] GET " << url << "\n";
        return "response data";

        // Thêm middleware mới (rate limiting, retry...) → sửa thẳng vào đây
    }
};

int main() {
    HttpClient client;
    client.enableLogging = true;
    client.enableAuth    = true;
    client.send("https://api.example.com/users");
}