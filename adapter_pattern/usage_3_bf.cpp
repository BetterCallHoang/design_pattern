/*Trường hợp 3: Thống nhất nhiều nguồn dữ liệu khác nhau về 1 interface
Bài toán: App cần lấy thông tin thời tiết từ nhiều API khác nhau (OpenWeather, WeatherBit, AccuWeather) – mỗi API trả về format hoàn toàn khác nhau.*/
#include <iostream>
#include <string>

// Mỗi API có response format riêng
struct OpenWeatherResponse {
    double temp_kelvin;
    int    humidity_percent;
    std::string weather_description;
};

struct WeatherBitResponse {
    double temp_celsius;
    double rh; // relative humidity
    std::string weather_text;
};

class WeatherApp {
public:
    // Phải xử lý riêng cho từng API
    void showOpenWeather(const OpenWeatherResponse& r) {
        double celsius = r.temp_kelvin - 273.15;
        std::cout << "Nhiệt độ: " << celsius << "°C | "
                  << "Độ ẩm: " << r.humidity_percent << "% | "
                  << r.weather_description << "\n";
    }

    void showWeatherBit(const WeatherBitResponse& r) {
        std::cout << "Nhiệt độ: " << r.temp_celsius << "°C | "
                  << "Độ ẩm: " << r.rh << "% | "
                  << r.weather_text << "\n";
    }
    // Thêm AccuWeather → thêm method thứ 3, thứ 4...
    // Logic hiển thị bị lặp lại và không thể dùng chung
};