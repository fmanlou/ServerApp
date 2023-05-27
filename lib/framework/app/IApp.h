#pragma once

#include "IExtensionManager.h"

class IApp {
 public:
  virtual ~IApp() = default;
  virtual std::shared_ptr<IExtensionManager> extensionManager() = 0;
  virtual void exec(int argc, char **agrv) = 0;
  virtual void quit() = 0;
};