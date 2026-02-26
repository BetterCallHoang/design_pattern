#include <iostream>
#include <vector>
#include <string>

// ===== Component =====
class FileSystemComponent { // [Component]
public:
    virtual ~FileSystemComponent() = default;
    virtual void show(int indent = 0) = 0;
};

// ===== Leaf =====
class File : public FileSystemComponent { // [Leaf]
private:
    std::string name;
    int size;
public:
    File(const std::string& n, int s) : name(n), size(s) {}

    void show(int indent = 0) override {
        std::cout << std::string(indent, ' ')
                  << name << " (" << size << "KB)\n";
    }
};

// ===== Composite =====
class Folder : public FileSystemComponent { // [Composite]
private:
    std::string name;
    std::vector<FileSystemComponent*> children;

public:
    Folder(const std::string& n) : name(n) {}

    void add(FileSystemComponent* c) {
        children.push_back(c);
    }

    void show(int indent = 0) override {
        std::cout << std::string(indent, ' ')
                  << "Folder: " << name << "\n";

        for (auto child : children)
            child->show(indent + 2);
    }
};

int main() { // [Client]
    File f1("a.txt", 10);
    File f2("b.txt", 20);

    Folder root("root");
    root.add(&f1);
    root.add(&f2);

    root.show();
}