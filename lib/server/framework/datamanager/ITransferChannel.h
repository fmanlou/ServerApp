#pragma once

#include <memory>

#include "IUploadChannel.h"

template <typename T>
class ITransferChannel : public IUploadChannel<T> {
 public:
  virtual ~ITransferChannel() = default;
  virtual void addChannel(std::shared_ptr<IUploadChannel<T>> channel) = 0;
};