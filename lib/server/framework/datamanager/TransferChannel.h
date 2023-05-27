#pragma once

#include <memory>
#include <vector>

#include "ITransferChannel.h"

template <typename T>
void uploadHelper(std::vector<std::shared_ptr<IUploadChannel<T>>>& channels,
                  const T& value) {
  for (auto iter = channels.begin(); iter != channels.end();) {
    if (*iter) {
      (*iter)->upload(value);
      ++iter;
    } else {
      iter = channels.erase(iter);
    }
  }
}

template <typename T>
class TransferChannel : public ITransferChannel<T> {
 public:
  void upload(const T& value) override {
    std::lock_guard<std::mutex> lock(mutex_);
    uploadHelper(channels_, value);
  }

  void addChannel(std::shared_ptr<IUploadChannel<T>> channel) override {
    std::lock_guard<std::mutex> lock(mutex_);
    channels_.push_back(channel);
  }

 private:
  std::vector<std::shared_ptr<IUploadChannel<T>>> channels_;
  std::mutex mutex_;
};
