/*Trường hợp 2: Hành vi thay đổi hoàn toàn theo trạng thái (ATM)*/
/*🔴 Khi số state tăng lên → điều kiện lồng nhau rất phức tạp*/
class ATM {
    bool hasCard = false;
    bool authenticated = false;

public:
    void insertCard() {
        if (!hasCard) {
            hasCard = true;
        }
    }

    void withdraw() {
        if (hasCard && authenticated) {
            std::cout << "Withdraw money\n";
        } else {
            std::cout << "Not allowed\n";
        }
    }
};