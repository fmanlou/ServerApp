#pragma once

#include <memory>

#include "IExtension.h"

class Extension : public IExtension {
 public:
  explicit Extension(const std::string& id);
  std::string id() override;
  void initialize(IExtensionManager& manager) override;

 private:
  std::string id_;
};