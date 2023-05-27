#pragma once

#include <iostream>

class IExtensionManager;
class IExtension {
 public:
  virtual ~IExtension() = default;
  virtual std::string id() = 0;
  virtual void initialize(IExtensionManager& manager) = 0;
};
