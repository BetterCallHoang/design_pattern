/*Trường hợp 1: Không muốn lộ cấu trúc nội bộ của collection*/
#include <iostream>
#include <vector>

// ===== ConcreteAggregate =====
class SensorCollection {
public:
    std::vector<int> data;  // 🔴 Lộ cấu trúc bên trong

    void add(int value) {
        data.push_back(value);
    }
};

int main() { // [Client]
    SensorCollection sensors;
    sensors.add(10);
    sensors.add(20);
    sensors.add(30);

    // Client truy cập trực tiếp vector
    for (size_t i = 0; i < sensors.data.size(); ++i) {
        std::cout << sensors.data[i] << "\n";
    }

    return 0;
}