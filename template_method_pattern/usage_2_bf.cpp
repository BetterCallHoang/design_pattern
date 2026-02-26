/*Trường hợp 2: Muốn kiểm soát thứ tự thực thi (không cho subclass phá vỡ trình tự)
Không dùng Template Method
Subclass có thể tự gọi các bước tùy ý → dễ sai thứ tự.*/
class DataImporter {
public:
    virtual void run() = 0;
};

class CsvImporter : public DataImporter {
public:
    void run() override {
        // Có thể quên validate
        parse();
        save();
    }

    void parse() {}
    void validate() {}
    void save() {}
};