#pragma once

#include <chrono>

template <typename T>
class IDownloadChannel {
 public:
  virtual ~IDownloadChannel() = default;
  virtual bool timeWaitAnddownload(
      T& value, const std::chrono::microseconds& duration) = 0;
};
