#include <iostream>
#include <vector>
#include <memory>

// Observer interface
class IObserver {
public:
    virtual void onPriceChanged(double price) = 0;
    virtual ~IObserver() = default;
};
// Missing the Observerable Interface 
// Subject / Concrete Observable 
class Stock {
    double price = 0;
    std::vector<IObserver*> observers;
public:
    void subscribe(IObserver* o)   { observers.push_back(o); }
    void unsubscribe(IObserver* o) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), o),
            observers.end()
        );
    }
    void setPrice(double newPrice) {
        price = newPrice;
        notify(); // chỉ gọi interface, không biết observer là ai
    }
private:
    void notify() {
        for (auto* o : observers)
            o->onPriceChanged(price);
    }
};

// Concrete Observers – thêm bao nhiêu cũng được, không sửa Stock
class PriceBoard : public IObserver {
public:
    void onPriceChanged(double price) override {
        std::cout << "[Bảng giá] Giá mới: " << price << "\n";
    }
};

class Chart : public IObserver {
public:
    void onPriceChanged(double price) override {
        std::cout << "[Biểu đồ] Vẽ lại với giá: " << price << "\n";
    }
};

class AlertSystem : public IObserver {
public:
    void onPriceChanged(double price) override {
        if (price > 100)
            std::cout << "[Cảnh báo] Giá vượt ngưỡng: " << price << "\n";
    }
};
// End of Concrete Observers 
int main() {
    Stock stock;

    PriceBoard board;
    Chart chart;
    AlertSystem alert;
    // It should be 
    // if (boardRequest) {
    // stock.subcribe(&board)}
    stock.subscribe(&board);
    stock.subscribe(&chart);
    stock.subscribe(&alert);

    stock.setPrice(105.0);

    std::cout << "\n-- Bỏ theo dõi biểu đồ --\n\n";
    stock.unsubscribe(&chart);

    stock.setPrice(98.0);
}
```

**Output:**
```
[Bảng giá] Giá mới: 105
[Biểu đồ] Vẽ lại với giá: 105
[Cảnh báo] Giá vượt ngưỡng: 105

-- Bỏ theo dõi biểu đồ --

[Bảng giá] Giá mới: 98
[Cảnh báo] Giá vượt ngưỡng: ... (không vượt nên không in)