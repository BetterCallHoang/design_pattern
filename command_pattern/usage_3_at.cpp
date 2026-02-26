#include <iostream>
#include <memory>
#include <array>

// Command interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo()    = 0;
    virtual ~Command() = default;
};

// Receivers
class Light {
    std::string location;
public:
    Light(const std::string& loc) : location(loc) {}
    void on()  { std::cout << "[Đèn " << location << "] Bật\n"; }
    void off() { std::cout << "[Đèn " << location << "] Tắt\n"; }
};

class AirConditioner {
    int temperature;
public:
    AirConditioner() : temperature(25) {}
    void on(int temp) {
        temperature = temp;
        std::cout << "[Máy lạnh] Bật, nhiệt độ: " << temp << "°C\n";
    }
    void off() { std::cout << "[Máy lạnh] Tắt\n"; }
    int getTemp() const { return temperature; }
};

// Concrete Commands
class LightOnCommand : public Command {
    Light& light;
public:
    LightOnCommand(Light& l) : light(l) {}
    void execute() override { light.on(); }
    void undo()    override { light.off(); }
};

class LightOffCommand : public Command {
    Light& light;
public:
    LightOffCommand(Light& l) : light(l) {}
    void execute() override { light.off(); }
    void undo()    override { light.on(); }
};

class AcOnCommand : public Command {
    AirConditioner& ac;
    int temp;
    int prevTemp;
public:
    AcOnCommand(AirConditioner& a, int t) : ac(a), temp(t), prevTemp(t) {}
    void execute() override {
        prevTemp = ac.getTemp();
        ac.on(temp);
    }
    void undo() override { ac.on(prevTemp); }
};

class AcOffCommand : public Command {
    AirConditioner& ac;
    int prevTemp;
public:
    AcOffCommand(AirConditioner& a) : ac(a), prevTemp(25) {}
    void execute() override {
        prevTemp = ac.getTemp();
        ac.off();
    }
    void undo() override { ac.on(prevTemp); }
};

// Invoker – Remote không biết gì về thiết bị
class SmartRemote {
    // 4 nút, mỗi nút giữ 1 command
    std::array<Command*, 4> buttons = {nullptr, nullptr, nullptr, nullptr};
    Command* lastCommand = nullptr;
public:
    void setButton(int slot, Command* cmd) {
        buttons[slot] = cmd;
    }

    void pressButton(int slot) {
        if (slot < 0 || slot >= 4 || !buttons[slot]) return;
        buttons[slot]->execute();
        lastCommand = buttons[slot];
    }

    void pressUndo() {
        if (lastCommand) {
            lastCommand->undo();
            lastCommand = nullptr;
        }
    }
};

int main() {
    // Receivers
    Light light("Phòng khách");
    AirConditioner ac;

    // Commands
    LightOnCommand  lightOn(light);
    LightOffCommand lightOff(light);
    AcOnCommand     acOn(ac, 22);
    AcOffCommand    acOff(ac);

    // Gán vào remote – remote không biết Light hay AC là gì
    SmartRemote remote;
    remote.setButton(0, &lightOn);
    remote.setButton(1, &lightOff);
    remote.setButton(2, &acOn);
    remote.setButton(3, &acOff);

    remote.pressButton(0); // bật đèn
    remote.pressButton(2); // bật máy lạnh
    remote.pressButton(1); // tắt đèn

    std::cout << "\n-- Undo thao tác vừa rồi --\n";
    remote.pressUndo();    // bật lại đèn
}
```

**Output:**
```
[Đèn Phòng khách] Bật
[Máy lạnh] Bật, nhiệt độ: 22°C
[Đèn Phòng khách] Tắt

-- Undo thao tác vừa rồi --
[Đèn Phòng khách] Bật