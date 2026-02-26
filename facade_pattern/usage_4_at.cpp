#include <iostream>
#include <string>

// ===== Subsystem classes =====
class Calibrator { // [Subsystem]
public:
    void loadTable() { std::cout << "[CAL] load table\n"; }
    void apply()     { std::cout << "[CAL] apply\n"; }
};

class Processor { // [Subsystem]
public:
    void rangeCompress()   { std::cout << "[PROC] range compress\n"; }
    void azimuthCompress() { std::cout << "[PROC] azimuth compress\n"; }
    void multilook(int n)  { std::cout << "[PROC] multilook x" << n << "\n"; }
};

class Exporter { // [Subsystem]
public:
    void writeGeoTiff(const std::string& path) { std::cout << "[EXP] write " << path << "\n"; }
};

// ===== Facade: tập hợp các use-case cấp cao =====
class SarProcessingFacade { // [Facade]
    Calibrator cal; // [Subsystem member]
    Processor  proc; // [Subsystem member]
    Exporter   exp; // [Subsystem member]
public:
    // Use-case API #1
    void calibrateFocusExport(const std::string& outPath) {
        cal.loadTable();
        cal.apply();
        proc.rangeCompress();
        proc.azimuthCompress();
        exp.writeGeoTiff(outPath);
    }

    // Use-case API #2
    void focusMultilookExport(int looks, const std::string& outPath) {
        proc.rangeCompress();
        proc.azimuthCompress();
        proc.multilook(looks);
        exp.writeGeoTiff(outPath);
    }
};

// ===== Client =====
int main() { // [Client]
    SarProcessingFacade f; // [Facade object]
    f.calibrateFocusExport("slc.tif");
    f.focusMultilookExport(4, "grd.tif");
    return 0;
}