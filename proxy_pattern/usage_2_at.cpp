#include <iostream>
#include <string>

// ===== Subject =====
class IBankAccount { // [Subject]
public:
    virtual ~IBankAccount() = default;
    virtual void withdraw(double amount) = 0;
};

// ===== RealSubject =====
class BankAccount : public IBankAccount { // [RealSubject]
public:
    void withdraw(double amount) override {
        std::cout << "Withdraw " << amount << "\n";
    }
};1

// ===== Proxy =====
class BankAccountProxy : public IBankAccount { // [Proxy]
private:
    BankAccount realAccount;
    std::string role;

public:
    BankAccountProxy(const std::string& userRole)
        : role(userRole) {}

    void withdraw(double amount) override {
        if (role == "admin")
            realAccount.withdraw(amount);
        else
            std::cout << "Access denied\n";
    }
};

int main() { // [Client]
    IBankAccount* acc = new BankAccountProxy("user");
    acc->withdraw(500);
    delete acc;
}