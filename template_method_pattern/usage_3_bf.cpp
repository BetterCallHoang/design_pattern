/*Trường hợp 3: Muốn chia sẻ code chung nhưng cho phép tùy biến một phần*/
class ReportGenerator {
public:
    void generate(const std::string& type) {
        std::cout << "Load data\n";

        if (type == "PDF")
            std::cout << "Format PDF\n";
        else if (type == "HTML")
            std::cout << "Format HTML\n";

        std::cout << "Save file\n";
    }
};
/* Vi phạm Open-Closed Principle
Thêm loại mới → sửa class cũ*/