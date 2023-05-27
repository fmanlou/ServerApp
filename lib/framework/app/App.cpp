#include "App.h"

App::App() : App(std::make_shared<ExtensionManager>()) {}

App::App(const std::shared_ptr<IExtensionManager> &extensionManager)
    : extensionManager_(extensionManager) {
  extensionManager->initializeExtensions();
}

std::shared_ptr<IExtensionManager> App::extensionManager() {
  return extensionManager_;
}
