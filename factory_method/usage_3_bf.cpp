/*Tách biệt logic tạo và logic sử dụng */
#include <iostream>

class CreditCardPayment {
public:
    void pay(double amount) {
        std::cout << "Thanh toán " << amount << " qua Credit Card\n";
    }
};

class PaypalPayment {
public:
    void pay(double amount) {
        std::cout << "Thanh toán " << amount << " qua PayPal\n";
    }
};

class OrderService {
public:
    void checkout(const std::string& method, double amount) {
        // Tạo object và dùng object lẫn lộn trong cùng 1 chỗ
        // Muốn đổi cách tạo CreditCardPayment (thêm config, thêm bước)
        // → phải sửa OrderService dù nó không liên quan
        if (method == "credit") {
            CreditCardPayment p;
            p.pay(amount);
        } else if (method == "paypal") {
            PaypalPayment p;
            p.pay(amount);
        }
    }
};