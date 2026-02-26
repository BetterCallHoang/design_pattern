#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

// Component interface
class TextProcessor {
public:
    virtual std::string process(const std::string& text) const = 0;
    virtual ~TextProcessor() = default;
};

// Concrete Component – xử lý gốc, không làm gì cả
class PlainText : public TextProcessor {
public:
    std::string process(const std::string& text) const override {
        return text;
    }
};

// Base Decorator
class TextDecorator : public TextProcessor {
protected:
    std::unique_ptr<TextProcessor> processor;
public:
    TextDecorator(std::unique_ptr<TextProcessor> p) : processor(std::move(p)) {}
};

// Concrete Decorators
class UppercaseDecorator : public TextDecorator {
public:
    UppercaseDecorator(std::unique_ptr<TextProcessor> p)
        : TextDecorator(std::move(p)) {}

    std::string process(const std::string& text) const override {
        std::string result = processor->process(text);
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
};

class BracketDecorator : public TextDecorator {
public:
    BracketDecorator(std::unique_ptr<TextProcessor> p)
        : TextDecorator(std::move(p)) {}

    std::string process(const std::string& text) const override {
        return "[" + processor->process(text) + "]";
    }
};

class PrefixDecorator : public TextDecorator {
    std::string prefix;
public:
    PrefixDecorator(std::unique_ptr<TextProcessor> p, std::string pref)
        : TextDecorator(std::move(p)), prefix(std::move(pref)) {}

    std::string process(const std::string& text) const override {
        return prefix + processor->process(text);
    }
};

// Thêm tính năng mới – không sửa gì cũ
class TrimDecorator : public TextDecorator {
public:
    TrimDecorator(std::unique_ptr<TextProcessor> p)
        : TextDecorator(std::move(p)) {}

    std::string process(const std::string& text) const override {
        std::string result = processor->process(text);
        // Xóa khoảng trắng đầu cuối
        size_t start = result.find_first_not_of(" ");
        size_t end   = result.find_last_not_of(" ");
        return (start == std::string::npos) ? "" : result.substr(start, end - start + 1);
    }
};

int main() {
    // Chỉ uppercase
    auto tp1 = std::make_unique<UppercaseDecorator>(
                   std::make_unique<PlainText>());
    std::cout << tp1->process("hello world") << "\n";
    // → HELLO WORLD

    // Prefix trước, rồi uppercase, rồi bọc ngoặc
    auto tp2 = std::make_unique<BracketDecorator>(
                   std::make_unique<UppercaseDecorator>(
                       std::make_unique<PrefixDecorator>(
                           std::make_unique<PlainText>(), "info: ")));
    std::cout << tp2->process("hello world") << "\n";
    // → [INFO: HELLO WORLD]

    // Đổi thứ tự: uppercase trước, rồi prefix
    auto tp3 = std::make_unique<PrefixDecorator>(
                   std::make_unique<UppercaseDecorator>(
                       std::make_unique<PlainText>()), "LOG: ");
    std::cout << tp3->process("hello world") << "\n";
    // → LOG: HELLO WORLD

    // Trim + Bracket
    auto tp4 = std::make_unique<BracketDecorator>(
                   std::make_unique<TrimDecorator>(
                       std::make_unique<PlainText>()));
    std::cout << tp4->process("  hello world  ") << "\n";
    // → [hello world]
}
```

**Output:**
```
HELLO WORLD
[INFO: HELLO WORLD]
LOG: HELLO WORLD
[hello world]