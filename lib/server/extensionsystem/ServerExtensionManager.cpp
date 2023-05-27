#include "ServerExtensionManager.h"

#include "CoreExtension.h"
#include "DataManagerExtension.h"
#include "ModuleExtensionFactory.h"
#include "ServerExtension.h"

ServerExtensionManager::ServerExtensionManager() { loadExtension(); }

void ServerExtensionManager::loadExtension() {
  registerExtension(Module::createEcgModuleExtension());
  registerExtension(Module::createSpo2ModuleExtension());
  registerExtension(std::make_shared<DataManager::DataManagerExtension>());
  registerExtension(std::make_shared<Core::CoreExtension>());
  registerExtension(std::make_shared<ServerExtension>());
}
