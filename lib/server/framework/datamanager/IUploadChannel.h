#pragma once

template <typename T>
class IUploadChannel {
 public:
  virtual ~IUploadChannel() = default;
  virtual void upload(const T& value) = 0;
};
