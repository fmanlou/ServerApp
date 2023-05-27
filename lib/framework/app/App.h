#pragma once

#include "ExtensionManager.h"
#include "IApp.h"

class App : public IApp {
 public:
  App();
  explicit App(const std::shared_ptr<IExtensionManager>& extensionManager);
  std::shared_ptr<IExtensionManager> extensionManager() override;

 protected:
  std::shared_ptr<IExtensionManager> extensionManager_;
};
