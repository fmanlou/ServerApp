#include <catch2/catch_all.hpp>

#include "QueueBiChannel.h"

struct QueueBiChannelTest {
  void testQueueBiChannel() {
    int value{0};
    queueBiChannel_.upload(value);
    int result;
    REQUIRE(queueBiChannel_.timeWaitAnddownload(result,
                                                std::chrono::milliseconds(0)));
    REQUIRE(result == value);
  }

  QueueBiChannel<int> queueBiChannel_;
};

TEST_CASE_METHOD(QueueBiChannelTest, "[QueueBiChannel]") {
  SECTION("testQueueBiChannel") { testQueueBiChannel(); }
}