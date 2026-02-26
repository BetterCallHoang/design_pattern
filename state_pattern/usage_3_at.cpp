#include <iostream>

class Player;

// ===== State =====
class PlayerState { // [State]
public:
    virtual ~PlayerState() = default;
    virtual void handleInput(Player* p, char input) = 0;
};

// ===== Context =====
class Player { // [Context]
private:
    PlayerState* state;

public:
    Player(PlayerState* s) : state(s) {}
    void setState(PlayerState* s) { state = s; }

    void handleInput(char input) {
        state->handleInput(this, input);
    }
};

// ===== Concrete States =====
class IdleState : public PlayerState { // [ConcreteState]
public:
    void handleInput(Player* p, char input) override;
};

class RunningState : public PlayerState { // [ConcreteState]
public:
    void handleInput(Player* p, char input) override;
};

void IdleState::handleInput(Player* p, char input) {
    if (input == 'r') {
        std::cout << "Start running\n";
        p->setState(new RunningState());
    }
}

void RunningState::handleInput(Player* p, char input) {
    if (input == 's') {
        std::cout << "Stop running\n";
        p->setState(new IdleState());
    }
}

int main() { // [Client]
    Player player(new IdleState());
    player.handleInput('r');
    player.handleInput('s');
}  

