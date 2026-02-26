/*Thêm chức năng vào object mà không muốn sửa class gốc*/
#include <iostream>
#include <string>

// Cách naive: tạo class cho mọi tổ hợp có thể
// 3 loại cà phê x 3 topping = bùng nổ class
class Espresso {
public:
    std::string getDesc() { return "Espresso"; }
    double getCost()      { return 20000; }
};

class EspressoWithMilk {
public:
    std::string getDesc() { return "Espresso + Sữa"; }
    double getCost()      { return 25000; }
};

class EspressoWithMilkAndSugar {
public:
    std::string getDesc() { return "Espresso + Sữa + Đường"; }
    double getCost()      { return 28000; }
};

class EspressoWithCream {
public:
    std::string getDesc() { return "Espresso + Kem"; }
    double getCost()      { return 27000; }
};

// Thêm 1 topping mới (trân châu) → phải tạo thêm hàng chục class nữa
// Americano + trân châu, Latte + trân châu + sữa... không thể kiểm soát

int main() {
    EspressoWithMilkAndSugar drink;
    std::cout << drink.getDesc() << " | " << drink.getCost() << " VND\n";
}