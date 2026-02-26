/*Trường hợp 2: Có nhiều cách duyệt khác nhau*/
class NumberCollection {
public:
    std::vector<int> data;

    void printForward() {
        for (size_t i = 0; i < data.size(); ++i)
            std::cout << data[i] << "\n";
    }

    void printBackward() {
        for (int i = data.size() - 1; i >= 0; --i)
            std::cout << data[i] << "\n";
    }
};