#include <catch2/catch_all.hpp>

#include "CoreExtensionMock.h"
#include "EcgConstants.h"
#include "ExtensionManagerMock.h"
#include "LoopIncParamProducer.h"
#include "ModuleExtension.h"
#include "ServerExtensionMock.h"

using Core::Mock::CoreExtensionMock;

struct ModuleExtensionTest {
  ModuleExtensionTest() {
    serverExtension_ = std::make_shared<ServerExtensionMock>();
    coreExtension_ = std::make_shared<CoreExtensionMock>();
    extension_ = std::make_shared<Module::ModuleExtension>(
        Ecg::Constants::kEcgExtensionId, Ecg::Constants::kHrParam,
        Ecg::Constants::kHrParamData);
  }

  void testId() {
    REQUIRE(extension_->id() == Ecg::Constants::kEcgExtensionId);
  }

  void testRegisterExtension() {
    extensionManager_.getExtension_ =
        [&](const std::string& id) -> std::shared_ptr<IExtension> {
      if (id == kGrpcServerExtensionId) return serverExtension_;
      return nullptr;
    };

    serverExtension_->registerMetaParam_ = [](const MetaParam& param) {
      REQUIRE(param == Ecg::Constants::kHrParam);
    };

    extension_->initialize(extensionManager_);
  };

  void testAddParamProducer() {
    extensionManager_.getExtension_ =
        [&](const std::string& id) -> std::shared_ptr<IExtension> {
      if (id == Core::Constants::kCoreExtensionId) return coreExtension_;
      return nullptr;
    };

    coreExtension_->addParamProducer_ = [](ParamProducer producer) {
      auto loopProducer = producer.target<LoopIncParamProducer>();
      REQUIRE(loopProducer != nullptr);
      const auto& data = loopProducer->data();
      REQUIRE(data == Ecg::Constants::kHrParamData);
    };

    extension_->initialize(extensionManager_);
  }

  std::shared_ptr<Module::ModuleExtension> extension_;
  std::shared_ptr<ServerExtensionMock> serverExtension_;
  std::shared_ptr<CoreExtensionMock> coreExtension_;
  ExtensionManagerMock extensionManager_;
};

TEST_CASE_METHOD(ModuleExtensionTest, "[ModuleExtension]") {
  SECTION("testId") { testId(); }
  SECTION("testRegisterExtension") { testRegisterExtension(); }
  SECTION("testAddParamProducer") { testAddParamProducer(); }
}
