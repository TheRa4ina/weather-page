#include <mutex>
#include <json/value.h>
#include <chrono>

class WeatherCache {
public:
    Json::Value getWeatherData();
private:
    void fetchWeatherDataAsJson();
    Json::Value data_;
    std::chrono::system_clock::time_point lastFetchTime_;
    std::mutex mutex_;
};
