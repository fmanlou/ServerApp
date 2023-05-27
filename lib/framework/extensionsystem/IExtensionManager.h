#pragma once

#include <iostream>
#include <memory>

#include "IExtension.h"

class IExtension;
class IExtensionManager {
 public:
  virtual ~IExtensionManager() = default;
  template <typename T>
  std::shared_ptr<T> getExtension(const std::string& id) {
    return std::dynamic_pointer_cast<T>(getExtension(id));
  }
  virtual std::shared_ptr<IExtension> getExtension(const std::string& id) = 0;
  virtual void registerExtension(
      const std::shared_ptr<IExtension> extension) = 0;
  virtual void initializeExtensions() = 0;
};
