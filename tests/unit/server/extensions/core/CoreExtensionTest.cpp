#include <catch2/catch_all.hpp>

#include "CoreConstants.h"
#include "CoreExtension.h"
#include "DataManagerExtensionMock.h"
#include "ExtensionManagerMock.h"
#include "QueueBiChannel.h"

using DataManager::Mock::DataManagerExtensionMock;

struct CoreExtensionTest {
  CoreExtensionTest() {
    dataManagerExtension_ = std::make_shared<DataManagerExtensionMock>();
  }

  void testId() {
    REQUIRE(coreExtension_.id() == Core::Constants::kCoreExtensionId);
  }

  void testAddParamProducer() {
    extensionManager_.getExtension_ =
        [&](const std::string& id) -> std::shared_ptr<IExtension> {
      if (id == DataManager::Constants::kDataManagerExtensionId)
        return dataManagerExtension_;
      return nullptr;
    };
    QueueBiChannel<Param> queue;
    dataManagerExtension_->paramUploadChannel_ = [&] { return &queue; };
    Param param{1, 1};
    ParamProducer producer = [&] { return param; };
    Param actual;
    coreExtension_.addParamProducer(producer);
    coreExtension_.initialize(extensionManager_);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    REQUIRE(queue.timeWaitAnddownload(actual, std::chrono::microseconds(0)));
    REQUIRE(param == actual);
  }

  Core::CoreExtension coreExtension_;
  std::shared_ptr<DataManagerExtensionMock> dataManagerExtension_;
  ExtensionManagerMock extensionManager_;
};

TEST_CASE_METHOD(CoreExtensionTest, "[CoreExtension]") {
  SECTION("testId") { testId(); }
  SECTION("testAddParamProducer") { testAddParamProducer(); }
}