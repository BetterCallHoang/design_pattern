/*Trường hợp 1: Workflow phức tạp, caller phải gọi đúng thứ tự*/

#include <iostream>
#include <string>

// ===== Subsystem classes (các thành phần phức tạp bên dưới) =====
class RFFrontend { // [Subsystem]
public:
    void configure(double freqGHz, double bwMHz) {
        std::cout << "[RF] configure " << freqGHz << "GHz, " << bwMHz << "MHz\n";
    }
    void warmup() { std::cout << "[RF] warmup\n"; }
};

class ClockSync { // [Subsystem]
public:
    void alignPPS() { std::cout << "[CLK] align PPS\n"; }
    void lock()     { std::cout << "[CLK] lock\n"; }
};

class DMAEngine { // [Subsystem]
public:
    void start() { std::cout << "[DMA] start\n"; }
    void stop()  { std::cout << "[DMA] stop\n"; }
};

class CaptureCore { // [Subsystem]
public:
    void arm()     { std::cout << "[CAP] arm\n"; }
    void trigger() { std::cout << "[CAP] trigger\n"; }
};

class Storage { // [Subsystem]
public:
    void save(const std::string& path) { std::cout << "[IO] save " << path << "\n"; }
};

// ===== Client (caller) =====
int main() { // [Client]
    RFFrontend  rf;
    ClockSync   clk;
    DMAEngine   dma;
    CaptureCore cap;
    Storage     io;

    // Client phải tự orchestration (dễ sai thứ tự)
    rf.configure(9.65, 300);
    rf.warmup();
    clk.alignPPS();
    clk.lock();
    cap.arm();
    dma.start();
    cap.trigger();
    dma.stop();
    io.save("capture.raw");

    return 0;
}