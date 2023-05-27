#include <catch2/catch_all.hpp>

#include "LoopIncParamProducer.h"

struct LoopIncrParamProducerTest {
  void testLoopIncParamProducer() {
    MetaLoopIncParam data(0, 0, 10);

    LoopIncParamProducer producer(data);
    REQUIRE(producer.data() == data);

    for (int i = data.lower; i <= data.upper; ++i) {
      auto param = producer();
      REQUIRE(param.index == data.index);
      REQUIRE(param.value == data.lower + i);
    }

    auto param = producer();
    REQUIRE(param.index == data.index);
    REQUIRE(param.value == data.lower);
  }

  void testBound() {
    REQUIRE(LoopIncParamProducer::bound(0, 0, 10) == 0);
    REQUIRE(LoopIncParamProducer::bound(10, 0, 10) == 10);
    REQUIRE(LoopIncParamProducer::bound(11, 0, 10) == 0);
  }
};

TEST_CASE_METHOD(LoopIncrParamProducerTest, "[LoopIncParamProducer]") {
  SECTION("testLoopIncParamProducer") { testLoopIncParamProducer(); }
  SECTION("testBound") { testBound(); }
}
