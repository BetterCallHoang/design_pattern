/*Trường hợp 1: Cấu trúc cây (File System)
🔴 Vấn đề:

Folder phải xử lý riêng File và Folder

Không thể lưu chung trong 1 container

Không đối xử đồng nhất
*/
#include <iostream>
#include <vector>
#include <string>

// Leaf
class File {
public:
    std::string name;
    int size;

    File(const std::string& n, int s) : name(n), size(s) {}

    void show() {
        std::cout << name << " (" << size << "KB)\n";
    }
};

// Composite (không có abstraction chung)
class Folder {
public:
    std::string name;
    std::vector<File*> files;       // 🔴 Chỉ chứa File
    std::vector<Folder*> folders;   // 🔴 Xử lý riêng

    Folder(const std::string& n) : name(n) {}

    void show() {
        std::cout << "Folder: " << name << "\n";

        for (File* f : files)
            f->show();

        for (Folder* sub : folders)
            sub->show();
    }
};

int main() { // [Client]
    File f1("a.txt", 10);
    File f2("b.txt", 20);

    Folder root("root");
    root.files.push_back(&f1);
    root.files.push_back(&f2);

    root.show();
}