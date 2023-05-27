#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>

namespace Disruptor {
template <typename T, typename TQueue = std::deque<T>>
class BlockingQueue {
 public:
  void push(const T& value) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      queue_.push_back(value);
    }
    condition_.notify_one();
  }

  void push(T&& value) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      queue_.push_back(std::move(value));
    }
    condition_.notify_one();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
  }

  template <typename TDuration>
  bool timeWaitAndPop(T& value, const TDuration& duration) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (!condition_.wait_for(lock, duration, [&] { return !queue_.empty(); }))
      return false;

    value = std::move(queue_.front());
    queue_.pop_front();
    return true;
  }

 private:
  TQueue queue_;
  mutable std::mutex mutex_;
  std::condition_variable condition_;
};

}  // namespace Disruptor