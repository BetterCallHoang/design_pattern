/*Trường hợp 1: Thay thuật toán tính toán (ví dụ: tính thuế)*/
#include <iostream>
#include <string>

class TaxCalculator { // [Context - nhưng nhét thuật toán vào đây]
public:
    double calculate(double amount, const std::string& country) {
        if (country == "VN")
            return amount * 0.1;
        else if (country == "US")
            return amount * 0.07;
        else if (country == "JP")
            return amount * 0.08;

        return amount;
    }
};

int main() { // [Client]
    TaxCalculator calc;
    std::cout << calc.calculate(1000, "VN") << "\n";
}