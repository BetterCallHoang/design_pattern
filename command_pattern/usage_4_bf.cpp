/*Trường hợp 4: Lên lịch thực thi hoặc thực thi có điều kiện
Bài toán: Hệ thống macro – ghi lại chuỗi thao tác rồi phát lại bất cứ lúc nào.*/
#include <iostream>
// Không có cách nào "ghi lại" hành động nếu nó chỉ là lời gọi hàm thẳng
// Hàm chạy xong là mất, không lưu lại được để phát lại
class App {
public:
    void doFormatBold()   { std::cout << "In đậm\n"; }
    void doFormatItalic() { std::cout << "In nghiêng\n"; }
    void doSave()         { std::cout << "Lưu file\n"; }
    // Muốn record macro "in đậm + in nghiêng + lưu" rồi replay?
    // Không có cách nào mà không viết thêm code đặc biệt
};
