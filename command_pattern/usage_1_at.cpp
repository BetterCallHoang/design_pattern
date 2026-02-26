#include <iostream>
#include <string>
#include <stack>
#include <memory>

// Command interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo()    = 0;
    virtual ~Command() = default;
};

// Receiver – đối tượng thực sự thực hiện hành động
class TextEditor {
    std::string text;
public:
    void insert(const std::string& str) { text += str; }

    void remove(int count) {
        if (count <= (int)text.size())
            text = text.substr(0, text.size() - count);
    }

    std::string getText() const { return text; }
};

// Concrete Commands
class InsertCommand : public Command {
    TextEditor& editor;
    std::string insertedText;
public:
    InsertCommand(TextEditor& e, const std::string& text)
        : editor(e), insertedText(text) {}

    void execute() override {
        editor.insert(insertedText);
        std::cout << "Insert '" << insertedText
                  << "' → Text: " << editor.getText() << "\n";
    }

    void undo() override {
        editor.remove(insertedText.size());
        std::cout << "Undo insert → Text: " << editor.getText() << "\n";
    }
};

class DeleteCommand : public Command {
    TextEditor& editor;
    std::string deletedText; // lưu lại để undo
    int count;
public:
    DeleteCommand(TextEditor& e, int n) : editor(e), count(n) {}

    void execute() override {
        std::string text = editor.getText();
        // Lưu phần sẽ bị xóa để có thể undo
        deletedText = text.substr(text.size() - count);
        editor.remove(count);
        std::cout << "Delete " << count
                  << " ký tự → Text: " << editor.getText() << "\n";
    }

    void undo() override {
        editor.insert(deletedText);
        std::cout << "Undo delete → Text: " << editor.getText() << "\n";
    }
};

// Invoker – quản lý và thực thi command
class EditorHistory {
    std::stack<std::unique_ptr<Command>> history;
    std::stack<std::unique_ptr<Command>> redoStack;
public:
    void execute(std::unique_ptr<Command> cmd) {
        cmd->execute();
        history.push(std::move(cmd));
        // Khi có hành động mới, xóa redo stack
        while (!redoStack.empty()) redoStack.pop();
    }

    void undo() {
        if (history.empty()) {
            std::cout << "Không có gì để undo\n";
            return;
        }
        auto cmd = std::move(history.top());
        history.pop();
        cmd->undo();
        redoStack.push(std::move(cmd));
    }

    void redo() {
        if (redoStack.empty()) {
            std::cout << "Không có gì để redo\n";
            return;
        }
        auto cmd = std::move(redoStack.top());
        redoStack.pop();
        cmd->execute();
        history.push(std::move(cmd));
    }
};

int main() {
    TextEditor editor;
    EditorHistory history;

    history.execute(std::make_unique<InsertCommand>(editor, "Hello"));
    history.execute(std::make_unique<InsertCommand>(editor, " World"));
    history.execute(std::make_unique<DeleteCommand>(editor, 5));

    std::cout << "\n-- Undo 2 lần --\n";
    history.undo();
    history.undo();

    std::cout << "\n-- Redo 1 lần --\n";
    history.redo();
}
```

**Output:**
```
Insert 'Hello' → Text: Hello
Insert ' World' → Text: Hello World
Delete 5 ký tự → Text: Hello

-- Undo 2 lần --
Undo delete → Text: Hello World
Undo insert → Text: Hello

-- Redo 1 lần --
Insert ' World' → Text: Hello World