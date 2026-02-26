#include <iostream>

// ===== Subsystem (driver đời 1) =====
class DMA_v1 { // [Subsystem]
public:
    void run()  { std::cout << "[DMA_v1] run\n"; }
    void halt() { std::cout << "[DMA_v1] halt\n"; }
};

// ===== Subsystem (driver đời 2 - API khác) =====
class DMA_v2 { // [Subsystem]
public:
    void startTransfer() { std::cout << "[DMA_v2] startTransfer\n"; }
    void stopTransfer()  { std::cout << "[DMA_v2] stopTransfer\n"; }
};

// ===== Facade (API ổn định cho phía trên) =====
class RecorderFacade { // [Facade]
    // Chọn 1 loại driver ở đây (đổi driver chỉ sửa trong facade)
    // DMA_v1 dma; // [Subsystem member]
    DMA_v2 dma;    // [Subsystem member]
public:
    void recordOnce() {
        // Nếu dùng v1:
        // dma.run();
        // std::cout << "[REC] recording...\n";
        // dma.halt();

        // Nếu dùng v2:
        dma.startTransfer();
        std::cout << "[REC] recording...\n";
        dma.stopTransfer();
    }
};

// ===== Client (service chỉ biết facade) =====
class RecorderService { // [Client]
    RecorderFacade& facade; // [Depends on Facade]
public:
    RecorderService(RecorderFacade& f) : facade(f) {}
    void record() { facade.recordOnce(); }
};

int main() { // [Client]
    RecorderFacade facade;     // [Facade object]
    RecorderService s(facade); // [Client uses Facade]
    s.record();
    return 0;
}