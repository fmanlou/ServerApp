#include <catch2/catch_all.hpp>

#include "ExtensionManagerMock.h"
#include "GrpcServerConstants.h"
#include "ServerApp.h"
#include "ServerExtensionMock.h"

struct ServerAppTest {
  ServerAppTest() {
    serverExtension_ = std::make_shared<ServerExtensionMock>();
    extensionManager_ = std::make_shared<ExtensionManagerMock>();
    app_ = std::make_shared<ServerApp>(extensionManager_);
    extensionManager_->getExtension_ = [&](const std::string& id) {
      REQUIRE(id == kGrpcServerExtensionId);
      return serverExtension_;
    };
  }

  void testDefaultIpAndPort() {
    serverExtension_->build_ = [&](const std::string& address) {
      REQUIRE(address == "0.0.0.0:50051");
    };
    app_->exec(0, nullptr);
  }

  void testSetIpAndPortByString() {
    serverExtension_->build_ = [&](const std::string& address) {
      REQUIRE(address == "127.0.0.1:50051");
    };
    app_->run("127.0.0.1", "50051");
  }

  void testSetIpAndPortByArgv() {
    const char* argv[] = {"ServerApp", "127.0.0.1", "50052"};
    serverExtension_->build_ = [&](const std::string& address) {
      REQUIRE(address == "127.0.0.1:50052");
    };
    app_->exec(3, const_cast<char**>(argv));
  }

  void testExtensionManagerNotNull() {
    ServerApp app;
    REQUIRE(app.extensionManager() != nullptr);
  }

  void testQuit() {
    serverExtension_->wait_ = []() { REQUIRE(true); };
    serverExtension_->shutdown_ = []() { REQUIRE(true); };
    app_->exec(0, nullptr);
    app_->quit();
  }

  std::shared_ptr<ServerApp> app_{nullptr};
  std::shared_ptr<ServerExtensionMock> serverExtension_{nullptr};
  std::shared_ptr<ExtensionManagerMock> extensionManager_{nullptr};
};

TEST_CASE_METHOD(ServerAppTest, "[ServerApp]") {
  SECTION("testDefaultIpAndPort") { testDefaultIpAndPort(); }
  SECTION("testSetIpAndPortByString") { testSetIpAndPortByString(); }
  SECTION("testSetIpAndPortByArgv") { testSetIpAndPortByArgv(); }
  SECTION("testExtensionManagerNotNull") { testExtensionManagerNotNull(); }
  SECTION("testQuit") { testQuit(); }
}