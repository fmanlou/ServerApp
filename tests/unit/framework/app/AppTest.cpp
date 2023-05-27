#include <catch2/catch_all.hpp>

#include "App.h"

struct AppTest : public App {
  void exec(int argc, char** argv) override {}
  void quit() override {}
  void testExtensionManagerNotNull() { REQUIRE(extensionManager() != nullptr); }
  void testExtensionManagerInitialized() { REQUIRE(false); }
};

TEST_CASE_METHOD(AppTest, "[App]") {
  SECTION("id") { testExtensionManagerNotNull(); }
}