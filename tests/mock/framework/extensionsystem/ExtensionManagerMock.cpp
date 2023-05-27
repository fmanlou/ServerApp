#include "ExtensionManagerMock.h"

std::shared_ptr<IExtension> ExtensionManagerMock::getExtension(
    const std::string &id) {
  if (getExtension_) return getExtension_(id);
  return std::shared_ptr<IExtension>();
}

void ExtensionManagerMock::registerExtension(
    const std::shared_ptr<IExtension> extension) {
  if (registerExtension_) registerExtension_(extension);
}

void ExtensionManagerMock::initializeExtensions() {
  if (initializeExtensions_) initializeExtensions_();
}
