/*Trường hợp 4: Cần API theo “use-case” (nhiều thao tác mức cao), không muốn caller tự ghép*/
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

// ===== Client =====
int main() { // [Client]
    Calibrator cal;
    Processor proc;
    Exporter exp;

    // Use-case A (lặp orchestration)
    cal.loadTable();
    cal.apply();
    proc.rangeCompress();
    proc.azimuthCompress();
    exp.writeGeoTiff("slc.tif");

    // Use-case B (lại lặp orchestration)
    proc.rangeCompress();
    proc.azimuthCompress();
    proc.multilook(4);
    exp.writeGeoTiff("grd.tif");

    return 0;
}