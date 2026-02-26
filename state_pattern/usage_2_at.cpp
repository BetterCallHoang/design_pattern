#include <iostream>

class ATM;

// ===== State =====
class ATMState { // [State]
public:
    virtual ~ATMState() = default;
    virtual void insertCard(ATM* atm) {}
    virtual void withdraw(ATM* atm) {}
};

// ===== Context =====
class ATM { // [Context]
private:
    ATMState* state;

public:
    ATM(ATMState* s) : state(s) {}

    void setState(ATMState* s) { state = s; }

    void insertCard() { state->insertCard(this); }
    void withdraw() { state->withdraw(this); }
};

// ===== Concrete States =====
class NoCardState : public ATMState { // [ConcreteState]
public:
    void insertCard(ATM* atm) override;
};

class HasCardState : public ATMState { // [ConcreteState]
public:
    void withdraw(ATM* atm) override {
        std::cout << "Withdraw money\n";
    }
};

void NoCardState::insertCard(ATM* atm) {
    std::cout << "Card inserted\n";
    atm->setState(new HasCardState());
}

int main() { // [Client]
    ATM atm(new NoCardState());
    atm.insertCard();
    atm.withdraw();
}