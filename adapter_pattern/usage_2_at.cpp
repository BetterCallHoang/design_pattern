#include <iostream>
#include <string>
#include <memory>

// Interface mới – KHÔNG đổi / Target 
class IPaymentProcessor {
public:
    virtual bool processPayment(double amount,
                                const std::string& currency) = 0;
    virtual void refund(double amount) = 0;
    virtual ~IPaymentProcessor() = default;
};

// Class cũ – KHÔNG đổi, KHÔNG viết lại /  Adaptee 
class OldPaymentGateway {
public:
    int makeTransaction(int amountInCents, const std::string& curr) {
        std::cout << "[OldGateway] Giao dịch "
                  << amountInCents << " cents (" << curr << ")\n";
        return 200;
    }
    void reverseTransaction(int amountInCents) {
        std::cout << "[OldGateway] Hoàn tiền "
                  << amountInCents << " cents\n";
    }
};

// Adapter – chuyển đổi OldGateway sang IPaymentProcessor
class PaymentGatewayAdapter : public IPaymentProcessor {
    OldPaymentGateway oldGateway;
    double lastAmount = 0;

    int toCents(double amount) const {
        return (int)(amount * 100);
    }

public:
    bool processPayment(double amount,
                        const std::string& currency) override {
        lastAmount = amount;
        // Chuyển đổi tập trung tại 1 chỗ
        int result = oldGateway.makeTransaction(toCents(amount), currency);
        return result == 200;
    }

    void refund(double amount) override {
        oldGateway.reverseTransaction(toCents(amount));
    }
};

// Service mới chỉ biết IPaymentProcessor / Client
class CheckoutService {
    IPaymentProcessor& processor;
public:
    CheckoutService(IPaymentProcessor& p) : processor(p) {}

    void checkout(double amount, const std::string& currency) {
        std::cout << "Xử lý đơn hàng " << amount << " " << currency << "\n";
        if (processor.processPayment(amount, currency))
            std::cout << "Thanh toán thành công!\n";
        else {
            std::cout << "Thanh toán thất bại, hoàn tiền...\n";
            processor.refund(amount);
        }
    }
};

int main() {
    PaymentGatewayAdapter adapter;
    CheckoutService checkout(adapter);

    checkout.checkout(500000, "VND");

    // Ngày mai có NewPaymentGateway?
    // Viết NewGatewayAdapter, thay 1 dòng ở main
    // CheckoutService không cần sửa
}
```

**Output:**
```
Xử lý đơn hàng 500000 VND
[OldGateway] Giao dịch 50000000 cents (VND)
Thanh toán thành công!