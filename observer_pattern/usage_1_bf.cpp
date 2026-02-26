/*Khi có quan hệ một-nhiều và cần đồng bộ trạng thái*/

#include <iostream>

class PriceBoard {
public:
    void update(double price) {
        std::cout << "[Bảng giá] Giá mới: " << price << "\n";
    }
};

class Chart {
public:
    void update(double price) {
        std::cout << "[Biểu đồ] Vẽ lại với giá: " << price << "\n";
    }
};

class AlertSystem {
public:
    void update(double price) {
        if (price > 100)
            std::cout << "[Cảnh báo] Giá vượt ngưỡng: " << price << "\n";
    }
};

// Stock phải biết tất cả các class kia → gắn cứng hoàn toàn
class Stock {
    PriceBoard board;
    Chart chart;
    AlertSystem alert;
public:
    void setPrice(double price) {
        // Muốn thêm "EmailNotifier" → phải vào đây sửa
        board.update(price);
        chart.update(price);
        alert.update(price);
    }
};

int main() {
    Stock stock;
    stock.setPrice(105.0);
}