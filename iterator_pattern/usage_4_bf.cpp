/*Trường hợp 4: Muốn tách logic duyệt khỏi business logic

Giả sử bạn có một danh sách tín hiệu (power theo range bin).
Collection chỉ nên lo lưu dữ liệu.
Business logic có thể thay đổi:

Tính tổng

Tìm peak

Lọc theo threshold

Xuất CSV

Tính trung bình

Nếu nhét logic vào collection → rất nhanh sẽ thành God class.*/
#include <iostream>
#include <vector>

// ===== ConcreteAggregate (bị phình to vì chứa cả logic) =====
class PowerCollection { // [ConcreteAggregate]
private:
    std::vector<double> data;

public:
    void add(double v) {
        data.push_back(v);
    }

    // 🔴 Business logic bị nhét vào collection
    double computeSum() {
        double sum = 0;
        for (size_t i = 0; i < data.size(); ++i)
            sum += data[i];
        return sum;
    }

    double findMax() {
        double max = data[0];
        for (size_t i = 1; i < data.size(); ++i)
            if (data[i] > max)
                max = data[i];
        return max;
    }

    void printAbove(double threshold) {
        for (size_t i = 0; i < data.size(); ++i)
            if (data[i] > threshold)
                std::cout << data[i] << "\n";
    }
};

int main() { // [Client]
    PowerCollection p;
    p.add(1.2);
    p.add(5.4);
    p.add(3.1);

    std::cout << "Sum: " << p.computeSum() << "\n";
    std::cout << "Max: " << p.findMax() << "\n";

    p.printAbove(2.0);

    return 0;
}