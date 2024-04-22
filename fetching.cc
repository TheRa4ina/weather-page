#include <drogon/drogon.h>
#include "env.h" // for api key

using namespace drogon;

Json::Value fetchWeatherDataAsJson() {
    auto client = drogon::HttpClient::newHttpClient("http://api.weatherapi.com");
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::Post);
    req->setPath("/v1/forecast.json");
    req->setParameter("key", API_KEY);
    req->setParameter("q", "Moscow");
    req->setParameter("days", "3");
    req->setParameter("lang", "ru");

    Json::Value res;
    std::promise<Json::Value> promise;
    auto future = promise.get_future();
    // Get the future associated with the promise
    res = *client->sendRequest(req).second->getJsonObject();

    return res;
}
