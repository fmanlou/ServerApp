#pragma once

#include "BlockingQueue.h"
#include "IBiChannel.h"

using Disruptor::BlockingQueue;

template <typename T>
class QueueBiChannel : public IBiChannel<T> {
 public:
  void upload(const T& value) override { queue_.push(value); }

  bool timeWaitAnddownload(T& value,
                           const std::chrono::microseconds& duration) override {
    return queue_.timeWaitAndPop(value, duration);
  }

 private:
  BlockingQueue<T> queue_;
};