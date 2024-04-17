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
    Json::Value json_result;
    client->sendRequest(req, [json_result](ReqResult result, const HttpResponsePtr& response) {
        if (result != ReqResult::Ok) {
            LOG_ERROR << "error while sending request to server! result:" << result <<'\n';
            throw "error sending request";
        }
        json_result = *(response->getJsonObject());

     });
    return json_result;
}