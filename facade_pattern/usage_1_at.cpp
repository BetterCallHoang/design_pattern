#include <iostream>
#include <string>

// ===== Subsystem classes =====
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

// ===== Facade (mặt tiền đơn giản hóa subsystem) =====
class SarCaptureFacade { // [Facade]
    RFFrontend  rf;   // [Subsystem member]
    ClockSync   clk;  // [Subsystem member]
    DMAEngine   dma;  // [Subsystem member]
    CaptureCore cap;  // [Subsystem member]
    Storage     io;   // [Subsystem member]
public:
    void captureOnce(double freqGHz, double bwMHz, const std::string& outPath) {
        // Facade chịu trách nhiệm orchestration đúng thứ tự
        rf.configure(freqGHz, bwMHz);
        rf.warmup();
        clk.alignPPS();
        clk.lock();
        cap.arm();
        dma.start();
        cap.trigger();
        dma.stop();
        io.save(outPath);
    }
};

// ===== Client =====
int main() { // [Client]
    SarCaptureFacade sar; // [Facade object]
    sar.captureOnce(9.65, 300, "capture.raw");
    return 0;
}