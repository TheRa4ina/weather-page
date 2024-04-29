#include <drogon/drogon.h>
#include "WeatherCache.h"

using namespace drogon;
using Callback = std::function<void(const HttpResponsePtr&)>;
int main() {
    // TO-DO eng language support?
    //Set HTTP listener address and port
    setlocale(LC_ALL, "Russian");
    setlocale(LC_TIME, "en_US.UTF-8");
    WeatherCache weather;
    drogon::app()
        .addListener("127.0.0.1", 5555)
        .loadConfigFile("config.json")
        .registerHandler("/", [&weather](const HttpRequestPtr& req, Callback&& callback)
            {
                HttpViewData data;
                

                data.insert("weather_json", weather.getWeatherData());
                auto test = weather.getWeatherData()["forecast"]["forecastday"][1]["day"]["condition"]["icon"].asString();
                auto resp = HttpResponse::newHttpViewResponse("index.csp", data);
                callback(resp);
            })
        .run();

    return 0;
}
