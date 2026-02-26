/*Trường hợp 2: Tái sử dụng class cũ với interface mới
Bài toán: Hệ thống thanh toán cũ dùng OldPaymentGateway, hệ thống mới yêu cầu interface IPaymentProcessor – không muốn viết lại từ đầu.*/
#include <iostream>
#include <string>

// Interface mới hệ thống yêu cầu
class IPaymentProcessor {
public:
    virtual bool processPayment(double amount,
                                const std::string& currency) = 0;
    virtual void refund(double amount) = 0;
    virtual ~IPaymentProcessor() = default;
};

// Class cũ đang hoạt động tốt – không muốn sửa hay viết lại
class OldPaymentGateway {
public:
    // Interface hoàn toàn khác
    int makeTransaction(int amountInCents, const std::string& curr) {
        std::cout << "[OldGateway] Giao dịch "
                  << amountInCents << " cents (" << curr << ")\n";
        return 200; // HTTP 200 = success
    }
    void reverseTransaction(int amountInCents) {
        std::cout << "[OldGateway] Hoàn tiền "
                  << amountInCents << " cents\n";
    }
};

// Buộc phải viết lại toàn bộ logic gateway
// hoặc sửa toàn bộ code mới để dùng OldPaymentGateway trực tiếp
class CheckoutService {
    OldPaymentGateway gateway; // gắn cứng class cũ
public:
    void checkout(double amount) {
        // Phải tự chuyển đổi thủ công mỗi nơi gọi
        int cents = (int)(amount * 100);
        int result = gateway.makeTransaction(cents, "VND");
        if (result == 200)
            std::cout << "Thanh toán thành công\n";
    }
};