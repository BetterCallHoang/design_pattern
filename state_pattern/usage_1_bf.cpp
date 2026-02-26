/*Trường hợp 1: Máy trạng thái (FSM) – ví dụ TCP Connection*/
/*🔴 Vấn đề:

Logic trạng thái nằm chung trong 1 class

Mỗi lần thêm state → sửa nhiều chỗ

Vi phạm Open-Closed Principle*/
#include <iostream>
#include <string>

// [Context]
class TcpConnection {
public:
    enum State { CLOSED, LISTEN, ESTABLISHED };

private:
    State state = CLOSED;

public:
    void open() {
        if (state == CLOSED) {
            std::cout << "Opening connection\n";
            state = LISTEN;
        }
    }

    void send() {
        if (state == ESTABLISHED) {
            std::cout << "Sending data\n";
        } else {
            std::cout << "Cannot send in current state\n";
        }
    }

    void establish() {
        if (state == LISTEN) {
            std::cout << "Connection established\n";
            state = ESTABLISHED;
        }
    }
};