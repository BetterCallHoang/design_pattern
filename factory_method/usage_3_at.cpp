/* Bài toán: Hệ thống thanh toán – logic xử lý thanh toán không nên quan tâm đối tượng Payment được tạo ra như thế nào.*/

#include <iostream>
#include <memory>
#include <string>

// Product
class Payment {
public:
    virtual void pay(double amount) const = 0;
    virtual ~Payment() = default;
};

class CreditCardPayment : public Payment {
public:
    void pay(double amount) const override {
        // Dù logic khởi tạo CreditCard có phức tạp đến đâu
        // cũng chỉ nằm ở đây, không lọt vào OrderService
        std::cout << "Thanh toán " << amount << " qua Credit Card\n";
    }
};

class PaypalPayment : public Payment {
public:
    void pay(double amount) const override {
        std::cout << "Thanh toán " << amount << " qua PayPal\n";
    }
};

// Creator
class PaymentService {
public:
    virtual std::unique_ptr<Payment> createPayment() const = 0;
    virtual ~PaymentService() = default;
};

class CreditCardService : public PaymentService {
    std::unique_ptr<Payment> createPayment() const override {
        return std::make_unique<CreditCardPayment>();
    }
};
class PaypalService : public PaymentService {
    std::unique_ptr<Payment> createPayment() const override {
        return std::make_unique<PaypalPayment>();
    }
};

// OrderService chỉ biết interface PaymentService
// Hoàn toàn không biết CreditCard hay Paypal tồn tại
class OrderService {
    const PaymentService& paymentService;
public:
    OrderService(const PaymentService& ps) : paymentService(ps) {}

    void checkout(double amount) const {
        std::cout << "Xử lý đơn hàng...\n";
        auto payment = paymentService.createPayment(); // chỉ gọi factory
        payment->pay(amount);
        std::cout << "Hoàn tất!\n";
    }
};

int main() {
    CreditCardService ccService;
    OrderService order(ccService);
    order.checkout(500000);

    std::cout << "\n";

    PaypalService ppService;
    OrderService order2(ppService);
    order2.checkout(200000);
}
```

**Output:**
```
Xử lý đơn hàng...
Thanh toán 500000 qua Credit Card
Hoàn tất!

Xử lý đơn hàng...
Thanh toán 200000 qua PayPal
Hoàn tất!