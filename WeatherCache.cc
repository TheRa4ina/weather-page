#include "WeatherCache.h"
#include <drogon/drogon.h>
#include "env.h" // for api key

using namespace drogon;

Json::Value WeatherCache::getWeatherData() {
    if (data_ && std::chrono::system_clock::now() - lastFetchTime_ > std::chrono::minutes(15)
        || data_.isNull()) {
        LOG_INFO << "Fetching weather data";
        int tryTimes = 0;
        while (tryTimes < 2)
        {
            try
            {
                fetchWeatherDataAsJson();
                break;
            }
            catch (const char* err_message)
            {
                LOG_ERROR << "fetch failed " << err_message << ", trying again";
            }
            tryTimes++;
        }
    }
    std::lock_guard<std::mutex> lock(mutex_);
    return data_;
}

void WeatherCache::fetchWeatherDataAsJson() {
    auto client = drogon::HttpClient::newHttpClient("http://api.weatherapi.com");
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::Post);
    req->setPath("/v1/forecast.json");
    req->setParameter("key", API_KEY);
    req->setParameter("q", "Moscow");
    req->setParameter("days", "3");
    req->setParameter("lang", "ru");

    // Get the future associated with the promise
    data_ = *client->sendRequest(req).second->getJsonObject();
    auto req_res = client->sendRequest(req);
    if (req_res.first!=ReqResult::Ok) {
        LOG_ERROR << req_res.first;
        throw std::runtime_error("error sending request");
    }
    else {
        std::lock_guard<std::mutex> lock(mutex_);
        data_=*req_res.second->getJsonObject();
        lastFetchTime_ = std::chrono::system_clock::now();
    }
}
