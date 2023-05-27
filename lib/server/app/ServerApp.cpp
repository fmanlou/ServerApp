#include "ServerApp.h"

#include "ServerExtension.h"
#include "ServerExtensionManager.h"

using grpc::Server;

using std::string;
using std::string_view;

constexpr string_view default_ip = "0.0.0.0";
constexpr string_view default_port = "50051";

ServerApp::ServerApp() : App(std::make_shared<ServerExtensionManager>()) {}

ServerApp::ServerApp(const std::shared_ptr<IExtensionManager>& extensionManager)
    : App(extensionManager) {}

void ServerApp::run(const string& server_address) {
  if (extensionManager_ == nullptr) return;

  auto server =
      extensionManager_->getExtension<IServerExtension>(kGrpcServerExtensionId);

  if (server == nullptr) return;

  server->build(server_address);
  server->wait();
}

void ServerApp::run(const string& ip, const string& port) {
  run(ip + ":" + port);
}

void ServerApp::exec(int argc, char** argv) {
  string ip{default_ip};
  string port{default_port};
  if (argc >= 3) {
    ip = argv[1];
    port = argv[2];
  }
  run(ip, port);
}

void ServerApp::quit() {
  auto server =
      extensionManager_->getExtension<IServerExtension>(kGrpcServerExtensionId);

  if (server == nullptr) return;

  server->shutdown();
}
