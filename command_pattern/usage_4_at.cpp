#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Command {
public:
    virtual void execute() = 0;
    virtual std::string getName() const = 0;
    virtual ~Command() = default;
};

class FormatBoldCommand : public Command {
public:
    void execute() override { std::cout << "  [Format] In đậm\n"; }
    std::string getName() const override { return "FormatBold"; }
};

class FormatItalicCommand : public Command {
public:
    void execute() override { std::cout << "  [Format] In nghiêng\n"; }
    std::string getName() const override { return "FormatItalic"; }
};

class SaveCommand : public Command {
    std::string filename;
public:
    SaveCommand(const std::string& f) : filename(f) {}
    void execute() override { std::cout << "  [File] Lưu: " << filename << "\n"; }
    std::string getName() const override { return "Save:" + filename; }
};

class SpellCheckCommand : public Command {
public:
    void execute() override { std::cout << "  [Tool] Kiểm tra chính tả\n"; }
    std::string getName() const override { return "SpellCheck"; }
};

// Macro – lưu và phát lại chuỗi command
class Macro {
    std::string name;
    std::vector<std::shared_ptr<Command>> commands;
public:
    Macro(const std::string& n) : name(n) {}

    void record(std::shared_ptr<Command> cmd) {
        commands.push_back(cmd);
        std::cout << "[Record] Ghi: " << cmd->getName() << "\n";
    }

    void play() const {
        std::cout << "\n[Macro] Phát lại '" << name
                  << "' (" << commands.size() << " bước):\n";
        for (auto& cmd : commands)
            cmd->execute();
        std::cout << "[Macro] Xong!\n";
    }
};

int main() {
    // Ghi macro
    Macro morningMacro("Quy trình buổi sáng");
    morningMacro.record(std::make_shared<SpellCheckCommand>());
    morningMacro.record(std::make_shared<FormatBoldCommand>());
    morningMacro.record(std::make_shared<FormatItalicCommand>());
    morningMacro.record(std::make_shared<SaveCommand>("bao_cao.docx"));

    // Phát lại bất kỳ lúc nào, bao nhiêu lần cũng được
    morningMacro.play();

    std::cout << "\n-- Phát lại lần 2 --\n";
    morningMacro.play();
}
```

**Output:**
```
[Record] Ghi: SpellCheck
[Record] Ghi: FormatBold
[Record] Ghi: FormatItalic
[Record] Ghi: Save:bao_cao.docx

[Macro] Phát lại 'Quy trình buổi sáng' (4 bước):
  [Tool] Kiểm tra chính tả
  [Format] In đậm
  [Format] In nghiêng
  [File] Lưu: bao_cao.docx
[Macro] Xong!

-- Phát lại lần 2 --

[Macro] Phát lại 'Quy trình buổi sáng' (4 bước):
  [Tool] Kiểm tra chính tả
  [Format] In đậm
  [Format] In nghiêng
  [File] Lưu: bao_cao.docx
[Macro] Xong!