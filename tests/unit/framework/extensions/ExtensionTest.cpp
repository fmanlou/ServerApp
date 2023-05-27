#include <catch2/catch_all.hpp>

#include "Extension.h"

struct ExtensionTest {
  void testId() { REQUIRE(extension_.id() == "id"); }

 public:
  Extension extension_{"id"};
};

TEST_CASE_METHOD(ExtensionTest, "[Extension]") {
  SECTION("id") { testId(); }
}