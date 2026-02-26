/*Trường hợp 2: Access Control (Protection Proxy)*/
class BankAccount {
public:
    void withdraw(double amount) {
        std::cout << "Withdraw " << amount << "\n";
    }
};

int main() {
    BankAccount account;
    account.withdraw(1000000); // ai cũng rút được
}