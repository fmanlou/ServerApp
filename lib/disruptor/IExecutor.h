#pragma once

#include <functional>

class IExecutor {
 public:
  virtual ~IExecutor() = default;
  virtual void execute(std::function<void> &&task) = 0;
};