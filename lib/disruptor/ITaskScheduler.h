#pragma once

#include <functional>

class ITaskScheduler {
 public:
  virtual ~ITaskScheduler() = default;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void schedule(std::function<void()> &&task) = 0;
};
