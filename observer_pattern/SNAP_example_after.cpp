#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// ===============================
// 1. Observer Interface
// ===============================

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(int percent) = 0;
};

// ===============================
// 2. Subject Interface
// ===============================

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* obs) = 0;
    virtual void detach(Observer* obs) = 0;
    virtual void notify(int percent) = 0;
};

// ===============================
// 3. ProcessingEngine (Subject)
// ===============================

class ProcessingEngine : public Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* obs) override {
        observers.push_back(obs);
    }

    void detach(Observer* obs) override {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void notify(int percent) override {
        for (auto obs : observers) {
            obs->update(percent);
        }
    }

    void processTile(int percent) {
        std::cout << "Đang xử lý tile...\n";

        // Sau khi xử lý xong
        notify(percent);  // ✅ Thông báo cho tất cả Observer
    }
};

// ===============================
// 4. Concrete Observers
// ===============================

class ImageView : public Observer {
public:
    void update(int percent) override {
        std::cout << "ImageView: Cập nhật hiển thị ảnh ("
                  << percent << "%)\n";
    }
};

class ProgressBar : public Observer {
public:
    void update(int percent) override {
        std::cout << "ProgressBar: "
                  << percent << "% hoàn thành\n";
    }
};

class LogSystem : public Observer {
public:
    void update(int percent) override {
        std::cout << "Log: Đã xử lý xong "
                  << percent << "% dữ liệu\n";
    }
};

// ===============================
// 5. Client
// ===============================

int main() {
    ProcessingEngine engine;

    ImageView imageView;
    ProgressBar progressBar;
    LogSystem logSystem;

    // Đăng ký các observer
    engine.attach(&imageView);
    engine.attach(&progressBar);
    engine.attach(&logSystem);

    engine.processTile(50);

    return 0;
}