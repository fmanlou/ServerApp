#pragma once

#include <unordered_map>

#include "IExtensionManager.h"

class ExtensionManager : public IExtensionManager {
 public:
  std::shared_ptr<IExtension> getExtension(const std::string& id) override;
  void registerExtension(const std::shared_ptr<IExtension> extension) override;
  void initializeExtensions() override;

 private:
  std::unordered_map<std::string, std::shared_ptr<IExtension> > extensionMap_;
};