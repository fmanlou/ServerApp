#include <catch2/catch_all.hpp>
#include <thread>

#include "BlockingQueue.h"

class BlockingQueueBenchmark {
 public:
  void benchmark(int count = 10000) {
    std::thread producer([&] {
      for (auto i = 0; i < count; ++i) {
        queue_.push(i);
      }
    });
    std::thread consumer([&] {
      for (auto i = 0; i < count; ++i) {
        int value;
        queue_.timeWaitAndPop(value, std::chrono::milliseconds(100));
      }
    });
    producer.join();
    consumer.join();
  }

  Disruptor::BlockingQueue<int> queue_;
};

TEST_CASE_METHOD(BlockingQueueBenchmark, "[BlockingQueueBenchmark]") {
  BENCHMARK("BlockingQueueBenchmark") { benchmark(); };
}
