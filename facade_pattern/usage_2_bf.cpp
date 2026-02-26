/*Trường hợp 2: Muốn cô lập thay đổi bên trong subsystem (đổi driver/thư viện mà caller không đổi)*/
#include <iostream>

// ===== Subsystem (driver đời 1) =====
class DMA_v1 { // [Subsystem]
public:
    void run()  { std::cout << "[DMA_v1] run\n"; }
    void halt() { std::cout << "[DMA_v1] halt\n"; }
};

// ===== Client (service bị gắn cứng vào subsystem cụ thể) =====
class RecorderService { // [Client]
    DMA_v1 dma; // [Direct dependency to a concrete Subsystem]
public:
    void record() {
        dma.run();
        std::cout << "[REC] recording...\n";
        dma.halt();
    }
};

int main() { // [Client]
    RecorderService s;
    s.record();

    // Nếu DMA đổi API => RecorderService phải sửa
    return 0;
}