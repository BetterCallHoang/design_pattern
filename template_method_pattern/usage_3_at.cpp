#include <iostream>

// ===== AbstractClass =====
class ReportGenerator { // [AbstractClass]
public:
    virtual ~ReportGenerator() = default;

    void generate() { // [Template Method]
        loadData();
        format();     // thay đổi theo subclass
        save();
    }

protected:
    void loadData() { std::cout << "Load data\n"; }
    virtual void format() = 0; // [Primitive Operation]
    void save() { std::cout << "Save file\n"; }
};

// ===== ConcreteClass =====
class PdfReport : public ReportGenerator { // [ConcreteClass]
protected:
    void format() override {
        std::cout << "Format PDF\n";
    }
};

class HtmlReport : public ReportGenerator { // [ConcreteClass]
protected:
    void format() override {
        std::cout << "Format HTML\n";
    }
};

int main() { // [Client]
    PdfReport pdf;
    HtmlReport html;

    pdf.generate();
    html.generate();

    return 0;
}