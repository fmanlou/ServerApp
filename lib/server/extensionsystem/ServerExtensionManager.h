#pragma once

#include <unordered_map>

#include "ExtensionManager.h"

class ServerExtensionManager : public ExtensionManager {
 public:
  ServerExtensionManager();

 private:
  void loadExtension();
};