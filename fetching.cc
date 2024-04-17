#include <drogon/drogon.h>
#include <future>
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
    client->sendRequest(req, [&promise](ReqResult result, const HttpResponsePtr& response) {
        if (result != ReqResult::Ok) {
            LOG_ERROR << "error while sending request to server! result:" << result <<'\n';
            throw "error sending request";
        }
        promise.set_value(*response->getJsonObject());
    });
    res = future.get();

    return res;
}
