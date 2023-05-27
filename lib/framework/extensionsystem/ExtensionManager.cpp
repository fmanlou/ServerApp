#include "ExtensionManager.h"

std::shared_ptr<IExtension> ExtensionManager::getExtension(
    const std::string &id) {
  auto it = extensionMap_.find(id);
  if (it != extensionMap_.end()) {
    return it->second;
  }
  return std::shared_ptr<IExtension>();
}

void ExtensionManager::registerExtension(
    const std::shared_ptr<IExtension> extension) {
  if (extension && getExtension(extension->id()) == nullptr) {
    extensionMap_[extension->id()] = extension;
  }
}

void ExtensionManager::initializeExtensions() {
  for (auto &extension : extensionMap_) {
    if (extension.second) extension.second->initialize(*this);
  }
}
