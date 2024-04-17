#include <gtest/gtest.h>
#include <fetching.h>

TEST(fetching, fetching_currentConditionIcon_IconUrl)
{
	Json::Value json = fetchWeatherDataAsJson();
	Json::Value error_code = json["error"]["code"];

	EXPECT_TRUE(error_code.isNull()) << "error code is "<<error_code.asInt();
}
