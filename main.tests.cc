#include <gtest/gtest.h>
#include <fetching.h>
#include <future>
#include <drogon/drogon.h>
#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>

TEST(fetching, fetching_currentConditionIcon_IconUrl)
{
	Json::Value json = fetchWeatherDataAsJson();
	Json::Value error_code = json["error"]["code"];

	ASSERT_TRUE(error_code.isNull()) << "error code is "<<error_code.asInt();
	ASSERT_FALSE(json.isNull());
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