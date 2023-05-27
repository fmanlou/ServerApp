#pragma once

#include <functional>
#include <unordered_map>

#include "IExtensionManager.h"

struct ExtensionManagerMock : public IExtensionManager {
  std::shared_ptr<IExtension> getExtension(const std::string& id) override;
  void registerExtension(const std::shared_ptr<IExtension> extension) override;
  void initializeExtensions() override;

  std::function<std::shared_ptr<IExtension>(const std::string&)> getExtension_;
  std::function<void(const std::shared_ptr<IExtension>)> registerExtension_;
  std::function<void()> initializeExtensions_;
};