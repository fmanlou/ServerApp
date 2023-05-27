#include <catch2/catch_all.hpp>

#include "RingBuffer.h"

struct RingBufferTest {
  void testRingBuffer() {
    ringBuffer_[0] = 0;
    REQUIRE(ringBuffer_[0] == 0);
    ringBuffer_[1] = 1;
    REQUIRE(ringBuffer_[0] == 1);
    REQUIRE(ringBuffer_[-1] == 1);
  }

  Disruptor::RingBuffer<int, 1> ringBuffer_;
};

TEST_CASE_METHOD(RingBufferTest, "[RingBuffer]") {
  SECTION("testRingBuffer") { testRingBuffer(); }
}
