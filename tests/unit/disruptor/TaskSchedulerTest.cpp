#include <catch2/catch_all.hpp>

#include "TaskScheduler.h"

struct TaskSchedulerTest {
  void testSchedule() {
    std::atomic<bool> called{false};
    auto task = [&called] { called = true; };
    scheduler_.start();
    scheduler_.schedule(std::move(task));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    scheduler_.stop();
    REQUIRE(called);
  }

  TaskScheduler<1> scheduler_;
};

TEST_CASE_METHOD(TaskSchedulerTest, "[TaskScheduler]") {
  SECTION("testSchedule") { testSchedule(); }
}
