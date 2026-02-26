/*Trường hợp 1: Cần chức năng Undo/Redo
Bài toán: Text editor có thể hoàn tác và làm lại thao tác.*/
#include <iostream>
#include <string>

class TextEditor {
    std::string text;
public:
    void insertText(const std::string& str) {
        text += str;
        std::cout << "Text: " << text << "\n";
    }

    void deleteText(int count) {
        if (count <= (int)text.size())
            text = text.substr(0, text.size() - count);
        std::cout << "Text: " << text << "\n";
    }

    // Muốn undo insertText thì sao?
    // Không có cách nào biết trước đã insert gì để mà xóa đi
    // Phải tự lưu lịch sử thủ công ở khắp nơi → rất lộn xộn
};

int main() {
    TextEditor editor;
    editor.insertText("Hello");
    editor.insertText(" World");
    editor.deleteText(5);
    // Muốn undo deleteText? → bó tay
}