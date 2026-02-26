/*Trường hợp 3: Tránh switch-case khổng lồ*/
class Player {
public:
    enum State { IDLE, RUNNING, JUMPING };

    State state = IDLE;

    void handleInput(char input) {
        switch (state) {
        case IDLE:
            if (input == 'r') state = RUNNING;
            break;
        case RUNNING:
            if (input == 'j') state = JUMPING;
            break;
        }
    }
};