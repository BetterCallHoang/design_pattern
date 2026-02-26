#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <stdexcept>

class Task {
public:
    virtual std::string getName() const = 0;
    virtual void execute()             = 0;
    virtual ~Task() = default;
};

// Concrete Tasks
class SendEmailTask : public Task {
    std::string recipient;
    std::string subject;
public:
    SendEmailTask(const std::string& r, const std::string& s)
        : recipient(r), subject(s) {}

    std::string getName() const override {
        return "SendEmail to " + recipient;
    }

    void execute() override {
        std::cout << "[Email] Gửi '" << subject
                  << "' tới " << recipient << "\n";
    }
};

class ResizeImageTask : public Task {
    std::string filename;
    int width, height;
public:
    ResizeImageTask(const std::string& f, int w, int h)
        : filename(f), width(w), height(h) {}

    std::string getName() const override {
        return "ResizeImage " + filename;
    }

    void execute() override {
        std::cout << "[Image] Resize '" << filename
                  << "' → " << width << "x" << height << "\n";
    }
};

class GenerateReportTask : public Task {
    std::string reportName;
public:
    GenerateReportTask(const std::string& name) : reportName(name) {}

    std::string getName() const override {
        return "GenerateReport: " + reportName;
    }

    void execute() override {
        std::cout << "[Report] Tạo báo cáo: " << reportName << "\n";
    }
};

// Task Queue với đầy đủ thông tin
class TaskQueue {
    std::queue<std::unique_ptr<Task>> tasks;
    int successCount = 0;
    int failCount    = 0;
public:
    void enqueue(std::unique_ptr<Task> task) {
        std::cout << "[Queue] Thêm task: " << task->getName() << "\n";
        tasks.push(std::move(task));
    }

    void processAll() {
        std::cout << "\n[Queue] Bắt đầu xử lý "
                  << tasks.size() << " tasks...\n\n";

        while (!tasks.empty()) {
            auto& task = tasks.front();
            std::cout << "[Queue] Chạy: " << task->getName() << "\n";

            try {
                task->execute();
                successCount++;
            } catch (const std::exception& e) {
                std::cout << "[Queue] Lỗi: " << e.what() << "\n";
                failCount++;
                // Có thể retry, log, alert ở đây vì biết task là gì
            }

            tasks.pop();
            std::cout << "\n";
        }

        std::cout << "[Queue] Xong! Thành công: " << successCount
                  << " | Thất bại: " << failCount << "\n";
    }
};

int main() {
    TaskQueue queue;

    queue.enqueue(std::make_unique<SendEmailTask>("minh@example.com", "Chào mừng"));
    queue.enqueue(std::make_unique<ResizeImageTask>("avatar.jpg", 200, 200));
    queue.enqueue(std::make_unique<GenerateReportTask>("Doanh thu tháng 3"));
    queue.enqueue(std::make_unique<SendEmailTask>("admin@example.com", "Báo cáo xong"));

    queue.processAll();
}
```

**Output:**
```
[Queue] Thêm task: SendEmail to minh@example.com
[Queue] Thêm task: ResizeImage avatar.jpg
[Queue] Thêm task: GenerateReport: Doanh thu tháng 3
[Queue] Thêm task: SendEmail to admin@example.com

[Queue] Bắt đầu xử lý 4 tasks...

[Queue] Chạy: SendEmail to minh@example.com
[Email] Gửi 'Chào mừng' tới minh@example.com

[Queue] Chạy: ResizeImage avatar.jpg
[Image] Resize 'avatar.jpg' → 200x200

[Queue] Chạy: GenerateReport: Doanh thu tháng 3
[Report] Tạo báo cáo: Doanh thu tháng 3

[Queue] Chạy: SendEmail to admin@example.com
[Email] Gửi 'Báo cáo xong' tới admin@example.com

[Queue] Xong! Thành công: 4 | Thất bại: 0