#include <iostream>
#include <string>
#include <memory>

// Interface thống nhất của hệ thống
struct WeatherData {
    double tempCelsius;
    double humidityPercent;
    std::string description;
};

class IWeatherProvider {
public:
    virtual WeatherData getWeather(const std::string& city) = 0;
    virtual ~IWeatherProvider() = default;
};

// API bên thứ 3 – không thể sửa
class OpenWeatherAPI {
public:
    struct Response {
        double temp_kelvin;
        int    humidity_percent;
        std::string weather_description;
    };
    Response fetch(const std::string& city) {
        std::cout << "[OpenWeather] Gọi API cho: " << city << "\n";
        return {303.15, 75, "Nhiều mây"}; // 30°C
    }
};

class WeatherBitAPI {
public:
    struct Response {
        double temp_celsius;
        double rh;
        std::string weather_text;
    };
    Response query(const std::string& city) {
        std::cout << "[WeatherBit] Gọi API cho: " << city << "\n";
        return {28.5, 80.0, "Có mưa nhỏ"};
    }
};

class AccuWeatherAPI {
public:
    struct Response {
        int temp_fahrenheit;
        int moisture;
        std::string condition;
    };
    Response request(const std::string& city) {
        std::cout << "[AccuWeather] Gọi API cho: " << city << "\n";
        return {95, 70, "Partly Cloudy"}; // 95°F = 35°C
    }
};

// Adapters – mỗi cái chuyển 1 API sang IWeatherProvider
class OpenWeatherAdapter : public IWeatherProvider {
    OpenWeatherAPI api;
public:
    WeatherData getWeather(const std::string& city) override {
        auto r = api.fetch(city);
        return {
            r.temp_kelvin - 273.15,   // Kelvin → Celsius
            (double)r.humidity_percent,
            r.weather_description
        };
    }
};

class WeatherBitAdapter : public IWeatherProvider {
    WeatherBitAPI api;
public:
    WeatherData getWeather(const std::string& city) override {
        auto r = api.query(city);
        return { r.temp_celsius, r.rh, r.weather_text };
    }
};

class AccuWeatherAdapter : public IWeatherProvider {
    AccuWeatherAPI api;
public:
    WeatherData getWeather(const std::string& city) override {
        auto r = api.request(city);
        return {
            (r.temp_fahrenheit - 32) * 5.0 / 9.0, // °F → °C
            (double)r.moisture,
            r.condition
        };
    }
};

// App chỉ biết IWeatherProvider – không biết API nào đang chạy
class WeatherApp {
    IWeatherProvider& provider;
public:
    WeatherApp(IWeatherProvider& p) : provider(p) {}

    void display(const std::string& city) {
        auto data = provider.getWeather(city);
        std::cout << "  Nhiệt độ : " << data.tempCelsius    << "°C\n";
        std::cout << "  Độ ẩm    : " << data.humidityPercent << "%\n";
        std::cout << "  Tình trạng: " << data.description    << "\n\n";
    }
};

int main() {
    OpenWeatherAdapter openWeather;
    WeatherBitAdapter  weatherBit;
    AccuWeatherAdapter accuWeather;

    std::cout << "=== Dùng OpenWeather ===\n";
    WeatherApp app1(openWeather);
    app1.display("Hà Nội");

    std::cout << "=== Dùng WeatherBit ===\n";
    WeatherApp app2(weatherBit);
    app2.display("Hà Nội");

    std::cout << "=== Dùng AccuWeather ===\n";
    WeatherApp app3(accuWeather);
    app3.display("Hà Nội");
}
```

**Output:**
```
=== Dùng OpenWeather ===
[OpenWeather] Gọi API cho: Hà Nội
  Nhiệt độ : 30°C
  Độ ẩm    : 75%
  Tình trạng: Nhiều mây

=== Dùng WeatherBit ===
[WeatherBit] Gọi API cho: Hà Nội
  Nhiệt độ : 28.5°C
  Độ ẩm    : 80%
  Tình trạng: Có mưa nhỏ

=== Dùng AccuWeather ===
[AccuWeather] Gọi API cho: Hà Nội
  Nhiệt độ : 35°C
  Độ ẩm    : 70%
  Tình trạng: Partly Cloudy