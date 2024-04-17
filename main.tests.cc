#include <gtest/gtest.h>
#include <fetching.h>
#include <future>
#include <drogon/drogon.h>
#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>


class ApiCallTest : public testing::Test {
protected:
	ApiCallTest()
		: weather_json(fetchWeatherDataAsJson())
	{}

	const Json::Value weather_json;
};

TEST_F(ApiCallTest, fetching_getJson_jsonNotNullNoErrors)
{
	Json::Value error_code = weather_json["error"]["code"];

	ASSERT_TRUE(error_code.isNull()) << "error code is "<<error_code.asInt() <<"check https://www.weatherapi.com/docs/ for more info";
	ASSERT_FALSE(weather_json.isNull()) << "something went horribly wrong";
}

TEST_F(ApiCallTest, fetching_getCurrentConditionIconURL_iconURLNotNull) {
	Json::Value icon_url= weather_json["current"]["condition"]["icon"];

	ASSERT_FALSE(icon_url.isNull());
}

TEST_F(ApiCallTest, fetching_getTommorowsForecast_tommorowsForecastNotNull) {
	Json::Value tommorows_forecast = weather_json["forecast"]["forecastday"][1];
	ASSERT_FALSE(tommorows_forecast.isNull());
}


// DO NOT MODIFY BELOW
using namespace drogon;
int main(int argc, char** argv) {
	std::promise<void> p1;
	std::future<void> f1 = p1.get_future();

	std::thread thr([&p1]()
		{
			app().getLoop()->queueInLoop([&p1]()
				{
					p1.set_value();
				});
			app().run();
		});

	f1.get();
	testing::InitGoogleTest(&argc, argv);
	int testStatus = RUN_ALL_TESTS();
	app().getLoop()->queueInLoop([]()
		{
			app().quit();
		});
	thr.join();
	return testStatus;
}