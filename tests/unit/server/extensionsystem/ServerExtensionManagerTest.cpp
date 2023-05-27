#include <catch2/catch_all.hpp>

#include "CoreConstants.h"
#include "DataManagerConstants.h"
#include "EcgConstants.h"
#include "GrpcServerConstants.h"
#include "ServerExtensionManager.h"
#include "Spo2Constants.h"

struct ServerExtensionManagerTest {
  void testLoadExtensions() {
    REQUIRE(extensionManager.getExtension(kGrpcServerExtensionId) != nullptr);
    REQUIRE(extensionManager.getExtension(Ecg::Constants::kEcgExtensionId) !=
            nullptr);
    REQUIRE(extensionManager.getExtension(Spo2::Constants::kSpo2ExtensionId) !=
            nullptr);
    REQUIRE(extensionManager.getExtension(Core::Constants::kCoreExtensionId) !=
            nullptr);
    REQUIRE(extensionManager.getExtension(
                DataManager::Constants::kDataManagerExtensionId) != nullptr);
  }

  ServerExtensionManager extensionManager;
};

TEST_CASE_METHOD(ServerExtensionManagerTest, "[ServerExtensionManager]") {
  SECTION("testLoadExtensions") { testLoadExtensions(); }
}