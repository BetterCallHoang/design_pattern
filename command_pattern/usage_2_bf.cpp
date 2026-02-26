/*Trường hợp 2: Xếp hàng đợi và thực thi lệnh sau (Task Queue)
Bài toán: Hệ thống xử lý tác vụ nền – nhận lệnh từ nhiều nơi, thực thi tuần tự hoặc theo lịch.*/
#include <iostream>
#include <string>
#include <queue>
#include <functional>

class TaskRunner {
    // Dùng function pointer hoặc lambda – không thể lưu thêm metadata
    // không biết task là gì, không thể log, không thể retry
    std::queue<std::function<void()>> tasks;
public:
    void addTask(std::function<void()> task) {
        tasks.push(task);
    }

    void run() {
        while (!tasks.empty()) {
            tasks.front()(); // gọi mù – không biết đây là task gì
            tasks.pop();
        }
    }
    // Muốn biết task nào lỗi? Muốn retry? Muốn log tên task?
    // → không có thông tin gì cả
};

int main() {
    TaskRunner runner;
    runner.addTask([]{ std::cout << "Gửi email\n"; });
    runner.addTask([]{ std::cout << "Resize ảnh\n"; });
    runner.run();
}