#include <iostream>
#include <memory>
#include <string>
//IComponent 
class HttpClient {
public:
    virtual std::string send(const std::string& url) const = 0;
    virtual ~HttpClient() = default;
};

// Base client
class BaseHttpClient : public HttpClient {
public:
    std::string send(const std::string& url) const override {
        std::cout << "[HTTP] GET " << url << "\n";
        return "response data";
    }
};

class HttpMiddleware : public HttpClient {
protected:
    std::unique_ptr<HttpClient> client;
public:
    HttpMiddleware(std::unique_ptr<HttpClient> c) : client(std::move(c)) {}
};

class LoggingMiddleware : public HttpMiddleware {
public:
    LoggingMiddleware(std::unique_ptr<HttpClient> c) : HttpMiddleware(std::move(c)) {}

    std::string send(const std::string& url) const override {
        std::cout << "[Log] Gửi request tới: " << url << "\n";
        auto response = client->send(url);
        std::cout << "[Log] Nhận response\n";
        return response;
    }
};

class AuthMiddleware : public HttpMiddleware {
    std::string token;
public:
    AuthMiddleware(std::unique_ptr<HttpClient> c, std::string t)
        : HttpMiddleware(std::move(c)), token(std::move(t)) {}

    std::string send(const std::string& url) const override {
        std::cout << "[Auth] Đính kèm token: " << token << "\n";
        return client->send(url);
    }
};

class CacheMiddleware : public HttpMiddleware {
public:
    CacheMiddleware(std::unique_ptr<HttpClient> c) : HttpMiddleware(std::move(c)) {}

    std::string send(const std::string& url) const override {
        std::cout << "[Cache] Kiểm tra cache cho: " << url << "... miss\n";
        auto response = client->send(url);
        std::cout << "[Cache] Lưu response vào cache\n";
        return response;
    }
};

int main() {
    std::cout << "=== Môi trường DEV (log + auth) ===\n";
    auto devClient =
        std::make_unique<LoggingMiddleware>(
            std::make_unique<AuthMiddleware>(
                std::make_unique<BaseHttpClient>(), "dev-token-123"));
    devClient->send("https://api.example.com/users");

    std::cout << "\n=== Môi trường PROD (auth + cache + log) ===\n";
    auto prodClient =
        std::make_unique<LoggingMiddleware>(
            std::make_unique<CacheMiddleware>(
                std::make_unique<AuthMiddleware>(
                    std::make_unique<BaseHttpClient>(), "prod-token-xyz")));
    prodClient->send("https://api.example.com/users");
}
```

**Output:**
```
=== Môi trường DEV (log + auth) ===
[Log] Gửi request tới: https://api.example.com/users
[Auth] Đính kèm token: dev-token-123
[HTTP] GET https://api.example.com/users
[Log] Nhận response

=== Môi trường PROD (auth + cache + log) ===
[Log] Gửi request tới: https://api.example.com/users
[Cache] Kiểm tra cache cho: https://api.example.com/users... miss
[Auth] Đính kèm token: prod-token-xyz
[HTTP] GET https://api.example.com/users
[Cache] Lưu response vào cache
[Log] Nhận response