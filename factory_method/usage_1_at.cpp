#include <iostream>
#include <memory>
#include <string>

// Interface Product
class Parser {
public:
    virtual void parse(const std::string& filename) const = 0;
    virtual ~Parser() = default;
};
// Concrete product 
class CSVParser : public Parser {
public:
    void parse(const std::string& f) const override {
        std::cout << "Đọc file CSV: " << f << "\n";
    }
};
// Concrete product 
class JSONParser : public Parser {
public:
    void parse(const std::string& f) const override {
        std::cout << "Đọc file JSON: " << f << "\n";
    }
};
// Concrete product 
class XMLParser : public Parser {
public:
    void parse(const std::string& f) const override {
        std::cout << "Đọc file XML: " << f << "\n";
    }
};

// Creator / Interface factory 
class DataProcessor {
public:
    virtual std::unique_ptr<Parser> createParser() const = 0;

    void process(const std::string& filename) const {
        auto parser = createParser(); // không cần biết loại cụ thể
        parser->parse(filename);
    }
    virtual ~DataProcessor() = default;
};
// Concrete factory 
class CSVProcessor  : public DataProcessor {
    std::unique_ptr<Parser> createParser() const override {
        return std::make_unique<CSVParser>();
    }
};
// Concrete factory 
class JSONProcessor : public DataProcessor {
    std::unique_ptr<Parser> createParser() const override {
        return std::make_unique<JSONParser>();
    }
};
// Concrete factory 
class XMLProcessor  : public DataProcessor {
    std::unique_ptr<Parser> createParser() const override {
        return std::make_unique<XMLParser>();
    }
};
// My concrete factory 
class ABCProcessor : public DataProcessor {
    std::unique_ptr<Parser> createParser() const override {
        return std::make_unique<ABCParser>();
    }
}
// Factory chọn Creator theo input runtime
std::unique_ptr<DataProcessor> makeProcessor(const std::string& type) {
    if (type == "csv")  return std::make_unique<CSVProcessor>();
    if (type == "json") return std::make_unique<JSONProcessor>();
    if (type == "xml")  return std::make_unique<XMLProcessor>();
    return nullptr;
}

int main() {
    std::string type;
    std::cout << "Nhập định dạng (csv/json/xml): ";
    std::cin >> type;

    // My code using pattern 

    // Code mẫu 
    auto processor = makeProcessor(type); // quyết định lúc runtime
    if (processor)
        processor->process("data.txt");
}