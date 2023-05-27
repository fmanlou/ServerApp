#include <catch2/catch_all.hpp>

#include "ExtensionManagerMock.h"
#include "ServerExtension.h"

struct ServerExtensionTest {
  ServerExtensionTest() {
    serverExtension = std::make_unique<ServerExtension>();
  }

  void testServiceNullptr() {
    serverExtension->build("localhost:50051");
    REQUIRE(true);
  }

  void testServerNullptrThenCallWait() {
    serverExtension->wait();
    REQUIRE(true);
  }

  void testServerNullptrThenCallShutdown() {
    serverExtension->shutdown();
    REQUIRE(true);
  }

  void testInitialize() {
    serverExtension->initialize(extensionManager);
    REQUIRE(true);
  }

  ExtensionManagerMock extensionManager;
  std::unique_ptr<ServerExtension> serverExtension;
};

TEST_CASE_METHOD(ServerExtensionTest, "[ServerExtension]") {
  SECTION("testServiceNullptr") { testServiceNullptr(); }
  SECTION("testServerNullptrThenCallWait") { testServerNullptrThenCallWait(); }
  SECTION("testServerNullptrThenCallShutdown") {
    testServerNullptrThenCallShutdown();
  }
  SECTION("testInitialize") { testInitialize(); }
}