#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "App.h"
#include "ExtensionManager.h"

class RealtimeService;

class ServerApp : public App {
 public:
  ServerApp();
  explicit ServerApp(
      const std::shared_ptr<IExtensionManager>& extensionManager);
  void exec(int argc, char** argv) override;
  void quit() override;
  void run(const std::string& server_address);
  void run(const std::string& ip, const std::string& port);
};
