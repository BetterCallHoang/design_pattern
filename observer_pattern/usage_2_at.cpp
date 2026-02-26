/* Khi muốn loose coupling – Subject không cần biết Observer là ai */
#include <iostream>
#include <vector>
#include <string>

// IObserver 
class IEventListener {
public:
    virtual void onEvent(const std::string& event) = 0;
    virtual ~IEventListener() = default;
};
// IObservable 
class EventManager {
    std::vector<IEventListener*> listeners;
public:
    void subscribe(IEventListener* l)   { listeners.push_back(l); }
    void publish(const std::string& event) {
        for (auto* l : listeners)
            l->onEvent(event);
    }
};

// Mỗi hệ thống hoàn toàn độc lập / Observer 
class UISystem : public IEventListener {
public:
    void onEvent(const std::string& e) override {
        if (e == "player_died")
            std::cout << "[UI] Hiển thị màn hình Game Over\n";
    }
};

class SoundSystem : public IEventListener {
public:
    void onEvent(const std::string& e) override {
        if (e == "player_died")
            std::cout << "[Sound] Phát nhạc thất bại\n";
    }
};

class AchievementSystem : public IEventListener {
public:
    void onEvent(const std::string& e) override {
        if (e == "player_died")
            std::cout << "[Achievement] Mở khóa: 'Chết lần đầu'\n";
    }
};

class Player {
    EventManager& events;
public:
    Player(EventManager& em) : events(em) {}

    void die() {
        std::cout << "Nhân vật đã chết!\n\n";
        events.publish("player_died"); // Player không biết ai lắng nghe
    }
};

int main() {
    EventManager events; //Concrete Observable  

    UISystem ui; //CObserver 
    SoundSystem sound; //CObserver 
    AchievementSystem achievement; //CObserver 

    events.subscribe(&ui);
    events.subscribe(&sound);
    events.subscribe(&achievement);

    Player player(events);
    player.die();
}
```

**Output:**
```
Nhân vật đã chết!

[UI] Hiển thị màn hình Game Over
[Sound] Phát nhạc thất bại
[Achievement] Mở khóa: 'Chết lần đầu'