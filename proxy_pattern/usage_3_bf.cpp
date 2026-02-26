/*Trường hợp 3: Logging / Monitoring Proxy
Nếu muốn log → sửa class này → vi phạm SRP.
*/
class DataProcessor {
public:
    void process() {
        std::cout << "Processing data\n";
    }
};