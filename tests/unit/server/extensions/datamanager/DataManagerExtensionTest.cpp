#include <catch2/catch_all.hpp>

#include "DataManagerConstants.h"
#include "DataManagerExtension.h"
#include "QueueBiChannel.h"

struct DataManagerExtensionTest {
  void testId() {
    REQUIRE(dataManagerExtension_.id() ==
            DataManager::Constants::kDataManagerExtensionId);
  }

  void testParamUploadChannel() {
    REQUIRE(dataManagerExtension_.paramUploadChannel() != nullptr);
  }

  void testAddParamUploadChannel() {
    auto channel = std::make_shared<QueueBiChannel<Param>>();
    dataManagerExtension_.addParamUploadChannel(channel);
    auto uploadChannel = dataManagerExtension_.paramUploadChannel();
    Param param{1, 1};
    uploadChannel->upload(param);
    Param actual;
    REQUIRE(channel->timeWaitAnddownload(actual, std::chrono::microseconds(0)));
    REQUIRE(param == actual);
  }

  DataManager::DataManagerExtension dataManagerExtension_;
};

TEST_CASE_METHOD(DataManagerExtensionTest, "[DataManagerExtension]") {
  SECTION("testId") { testId(); }
  SECTION("testParamUploadChannel") { testParamUploadChannel(); }
  SECTION("testAddParamUploadChannel") { testAddParamUploadChannel(); }
}