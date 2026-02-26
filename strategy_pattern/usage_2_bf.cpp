/*Trường hợp 2: Nhiều thuật toán nén dữ liệu*/
class Compressor {
public:
    void compress(const std::string& type) {
        if (type == "ZIP")
            std::cout << "Compress using ZIP\n";
        else if (type == "RAR")
            std::cout << "Compress using RAR\n";
    }
};