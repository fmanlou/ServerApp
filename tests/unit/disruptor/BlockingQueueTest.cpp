#include <catch2/catch_all.hpp>

#include "BlockingQueue.h"

struct BlockingQueueTest {
  void testEmpty() {
    int value;
    REQUIRE(queue_.empty());
    queue_.push(1);
    REQUIRE(!queue_.empty());
    queue_.timeWaitAndPop(value, std::chrono::milliseconds(0));
    REQUIRE(queue_.empty());
  }

  void testPushAndPop() {
    int value;
    REQUIRE(!queue_.timeWaitAndPop(value, std::chrono::milliseconds(0)));
    queue_.push(1);
    queue_.timeWaitAndPop(value, std::chrono::milliseconds(0));
    REQUIRE(value == 1);
    REQUIRE(!queue_.timeWaitAndPop(value, std::chrono::milliseconds(0)));
  }

  void pushReference() {
    int value = 1;
    queue_.push(value);
    value = 0;
    queue_.timeWaitAndPop(value, std::chrono::milliseconds(0));
    REQUIRE(value == 1);
  }

  Disruptor::BlockingQueue<int> queue_;
};

TEST_CASE_METHOD(BlockingQueueTest, "[BlockingQueue]") {
  SECTION("testEmpty") { testEmpty(); }
  SECTION("testPushAndPop") { testPushAndPop(); }
  SECTION("pushReference") { pushReference(); }
}
