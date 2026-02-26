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

// ===== Facade =====
class TelemetryFacade { // [Facade]
    ConfigDB db;           // [Subsystem member]
    NetworkClient net;     // [Subsystem member]
    TelemetryEncoder enc;  // [Subsystem member]
public:
    void sendTelemetry(const std::string& raw) {
        // Facade che giấu “nghi lễ”
        std::string host = db.read("telemetry.host");
        net.connect(host);
        std::string payload = enc.encode(raw);
        net.send(payload);
    }
};

// ===== Client =====
int main() { // [Client]
    TelemetryFacade tel; // [Facade object]
    tel.sendTelemetry("TEMP=42");
    return 0;
}