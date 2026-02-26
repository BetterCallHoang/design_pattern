/*Ý tưởng

- Mỗi thao tác là một Command

- Command có execute() và undo()

- Editor quản lý:

  + undoStack

  + redoStack
*/

#include <iostream>
#include <stack>
#include <memory>

// ===============================
// 1️⃣ Receiver: ImageViewport
// ===============================

class ImageViewport {
private:
    double scale = 1.0;
    double rotationAngle = 0.0;

public:
    void zoom(double factor) {
        scale *= factor;
        std::cout << "Zoom: scale = " << scale << "\n";
    }

    void setScale(double newScale) {
        scale = newScale;
        std::cout << "Set scale = " << scale << "\n";
    }

    double getScale() const {
        return scale;
    }

    void rotate(double angle) {
        rotationAngle += angle;
        std::cout << "Rotate: angle = " << rotationAngle << "\n";
    }

    void setRotation(double angle) {
        rotationAngle = angle;
        std::cout << "Set rotation = " << rotationAngle << "\n";
    }

    double getRotation() const {
        return rotationAngle;
    }
};

// ===============================
// 2️⃣ Command Interface
// ===============================

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// ===============================
// 3️⃣ Concrete Command: Zoom
// ===============================

class ZoomCommand : public Command {
private:
    ImageViewport& viewport;
    double factor;
    double previousScale;  // Lưu trạng thái trước

public:
    ZoomCommand(ImageViewport& vp, double f)
        : viewport(vp), factor(f) {}

    void execute() override {
        previousScale = viewport.getScale();
        viewport.zoom(factor);
    }

    void undo() override {
        viewport.setScale(previousScale);
    }
};

// ===============================
// 4️⃣ Concrete Command: Rotate
// ===============================

class RotateCommand : public Command {
private:
    ImageViewport& viewport;
    double angle;
    double previousAngle;

public:
    RotateCommand(ImageViewport& vp, double a)
        : viewport(vp), angle(a) {}

    void execute() override {
        previousAngle = viewport.getRotation();
        viewport.rotate(angle);
    }

    void undo() override {
        viewport.setRotation(previousAngle);
    }
};

// ===============================
// 5️⃣ Invoker: Editor
// ===============================

class Editor {
private:
    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;

public:
    void executeCommand(std::shared_ptr<Command> cmd) {
        cmd->execute();
        undoStack.push(cmd);

        // Khi có thao tác mới -> clear redo
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo() {
        if (undoStack.empty()) return;

        auto cmd = undoStack.top();
        undoStack.pop();

        cmd->undo();
        redoStack.push(cmd);
    }

    void redo() {
        if (redoStack.empty()) return;

        auto cmd = redoStack.top();
        redoStack.pop();

        cmd->execute();
        undoStack.push(cmd);
    }
};

// ===============================
// 6️⃣ Client
// ===============================

int main() {
    ImageViewport viewport;
    Editor editor;

    auto zoomCmd = std::make_shared<ZoomCommand>(viewport, 1.5);
    auto rotateCmd = std::make_shared<RotateCommand>(viewport, 90);

    editor.executeCommand(zoomCmd);
    editor.executeCommand(rotateCmd);

    std::cout << "\nUndo:\n";
    editor.undo();
    editor.undo();

    std::cout << "\nRedo:\n";
    editor.redo();
    editor.redo();

    return 0;
}