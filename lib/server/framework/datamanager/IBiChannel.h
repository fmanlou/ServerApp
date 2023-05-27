#pragma once

#include "IDownloadChannel.h"
#include "IUploadChannel.h"

template <typename T>
class IBiChannel : public IUploadChannel<T>, public IDownloadChannel<T> {
 public:
  virtual ~IBiChannel() = default;
};
