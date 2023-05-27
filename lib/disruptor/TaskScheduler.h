#pragma once

#include <atomic>
#include <thread>

#include "BlockingQueue.h"
#include "ITaskScheduler.h"

template <std::size_t N>
class TaskScheduler final : public ITaskScheduler {
 public:
  static_assert(N > 0, "N must be greater than 0");

  void start() override {
    if (running_) return;

    running_ = true;
    createThreads(N);
  }

  void stop() override {
    if (!running_) return;

    running_ = false;

    for (auto&& thread : threads_) {
      if (thread.joinable()) thread.join();
    }
  }

  void schedule(std::function<void()>&& task) override {
    tasks_.push(std::move(task));
  }

 private:
  void createThreads(int numberOfThreads) {
    for (std::size_t i = 0; i < numberOfThreads; ++i) {
      threads_.emplace_back([this]() { workingLoop(); });
    }
  }

  void workingLoop() {
    while (running_) {
      std::function<void()> task;
      while (tasks_.timeWaitAndPop(task, std::chrono::milliseconds(100)))
        task();
    }
  }

 private:
  std::atomic<bool> running_{false};
  Disruptor::BlockingQueue<std::function<void()>> tasks_;
  std::vector<std::thread> threads_;
};
