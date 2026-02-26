#include <iostream>

// Forward declaration
class TcpConnection;

// ===== State Interface =====
class TcpState { // [State]
public:
    virtual ~TcpState() = default;
    virtual void open(TcpConnection* ctx) {}
    virtual void send(TcpConnection* ctx) {}
    virtual void establish(TcpConnection* ctx) {}
};

// ===== Context =====
class TcpConnection { // [Context]
private:
    TcpState* state;

public:
    TcpConnection(TcpState* initial) : state(initial) {}

    void setState(TcpState* s) {
        state = s;
    }

    void open() { state->open(this); }
    void send() { state->send(this); }
    void establish() { state->establish(this); }
};

// ===== Concrete States =====
class ClosedState : public TcpState { // [ConcreteState]
public:
    void open(TcpConnection* ctx) override;
};

class ListenState : public TcpState { // [ConcreteState]
public:
    void establish(TcpConnection* ctx) override;
};

class EstablishedState : public TcpState { // [ConcreteState]
public:
    void send(TcpConnection* ctx) override {
        std::cout << "Sending data\n";
    }
};

// State transitions
void ClosedState::open(TcpConnection* ctx) {
    std::cout << "Opening connection\n";
    ctx->setState(new ListenState());
}

void ListenState::establish(TcpConnection* ctx) {
    std::cout << "Connection established\n";
    ctx->setState(new EstablishedState());
}

int main() { // [Client]
    TcpConnection conn(new ClosedState());

    conn.open();
    conn.establish();
    conn.send();

    return 0;
}