#include <iostream>

// ===== AbstractClass =====
class DataImporter { // [AbstractClass]
public:
    virtual ~DataImporter() = default;

    void import() { // [Template Method]
        openFile();
        parse();      // subclass phải override
        validate();   // subclass có thể override
        save();
    }

protected:
    void openFile() { std::cout << "Open file\n"; }

    virtual void parse() = 0;       // [Primitive Operation]
    virtual void validate() {       // [Hook - optional override]
        std::cout << "Default validation\n";
    }

    void save() { std::cout << "Save to database\n"; }
};

// ===== ConcreteClass =====
class CsvImporter : public DataImporter { // [ConcreteClass]
protected:
    void parse() override {
        std::cout << "Parse CSV\n";
    }

    void validate() override {
        std::cout << "Custom CSV validation\n";
    }
};

int main() { // [Client]
    CsvImporter importer;
    importer.import();
    return 0;
}