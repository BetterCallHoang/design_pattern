/*Trường hợp 3: Thay đổi thuật toán xử lý tín hiệu (rất sát thực tế)

Ví dụ:

FFT thường

Windowed FFT

Zero-padded FFT

GPU FFT*/

class FFTProcessor {
public:
    void process(int mode) {
        if (mode == 0)
            std::cout << "Standard FFT\n";
        else if (mode == 1)
            std::cout << "Windowed FFT\n";
    }
};