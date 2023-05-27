#include <catch2/catch_all.hpp>

#include "Extension.h"
#include "ExtensionManager.h"

struct ExtensionManagerTest {
  void testGetNotExistingExtension() {
    REQUIRE(extensionManager_.getExtension("id1") == nullptr);
  }

  void testRegisterNullExtension() {
    extensionManager_.registerExtension(nullptr);
    REQUIRE(true);
  }

  void testRegisterExtension() {
    auto ext1 = std::make_shared<Extension>("id1");
    extensionManager_.registerExtension(ext1);
    REQUIRE(extensionManager_.getExtension("id1") == ext1);
  }

  void testRegisterSameIdExtension() {
    auto ext1 = std::make_shared<Extension>("id1");
    auto ext2 = std::make_shared<Extension>("id1");
    extensionManager_.registerExtension(ext1);
    extensionManager_.registerExtension(ext2);
    REQUIRE(extensionManager_.getExtension("id1") == ext1);
  }

 public:
  ExtensionManager extensionManager_;
};

TEST_CASE_METHOD(ExtensionManagerTest, "[ExtensionManager]") {
  SECTION("testGetNotExistingExtension") { testGetNotExistingExtension(); }
  SECTION("registerExtension") { testRegisterExtension(); }
  SECTION("testRegisterNullExtension") { testRegisterNullExtension(); }
  SECTION("testRegisterSameIdExtension") { testRegisterSameIdExtension(); }
}
