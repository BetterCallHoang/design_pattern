/*Bài toán: UI Framework có Button. Người dùng framework muốn tạo Button theo style riêng (Windows, Mac) mà không fork code framework. */
 

// Framework bị "đóng cứng" – người dùng không thể thay Button
class Application {
public:
    void render() {
        // Hard-code WindowsButton ở đây
        // Người dùng framework KHÔNG THỂ thay bằng MacButton
        // mà không sửa code framework
        std::cout << "Render Windows Button\n";
    }
};