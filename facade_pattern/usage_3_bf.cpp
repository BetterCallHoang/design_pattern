/*Trường hợp 3: Giảm phụ thuộc (module trên không nên include/biết quá nhiều subsystem)*/
#include <iostream>
#include <string>

// ===== Subsystem classes =====
class ConfigDB { // [Subsystem]
public:
    std::string read(const std::string& key) {
        std::cout << "[DB] read " << key << "\n";
        return "telemetry.local";
    }
};

class NetworkClient { // [Subsystem]
public:
    void connect(const std::string& host) { std::cout << "[NET] connect " << host << "\n"; }
    void send(const std::string& payload) { std::cout << "[NET] send " << payload << "\n"; }
};

class TelemetryEncoder { // [Subsystem]
public:
    std::string encode(const std::string& raw) {
        std::cout << "[ENC] encode\n";
        return "ENC(" + raw + ")";
    }
};

// ===== Client =====
int main() { // [Client]
    // Client phải biết 3 subsystem và tự nối chúng
    ConfigDB db;
    NetworkClient net;
    TelemetryEncoder enc;

    std::string host = db.read("telemetry.host");
    net.connect(host);
    std::string payload = enc.encode("TEMP=42");
    net.send(payload);

    return 0;
}