#include "ServerExtension.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "CoreConstants.h"
#include "CoreExtension.h"
#include "DataManagerExtension.h"

using grpc::ServerBuilder;

ServerExtension::ServerExtension() {
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  realtimeService_ = std::make_unique<RealtimeService>();
}

void ServerExtension::build(const std::string& address) {
  if (realtimeService_ == nullptr) return;

  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(realtimeService_.get());
  server_ = std::move(builder.BuildAndStart());

  std::cout << "Server listening on " << address << std::endl;
}

void ServerExtension::wait() {
  if (server_ == nullptr) return;
  server_->Wait();
}

void ServerExtension::shutdown() {
  if (server_ == nullptr) return;
  server_->Shutdown();
}

void ServerExtension::registerMetaParam(const MetaParam& param) {
  if (realtimeService_ == nullptr) return;
  realtimeService_->registerMetaParam(param);
}

void ServerExtension::initialize(IExtensionManager& manager) {
  if (realtimeService_ == nullptr) return;

  auto dataManagerExtension =
      manager.getExtension<DataManager::DataManagerExtension>(
          DataManager::Constants::kDataManagerExtensionId);

  if (dataManagerExtension) {
    auto interface = [=](std::shared_ptr<ParamUploadChannel> channel) {
      dataManagerExtension->addParamUploadChannel(channel);
    };
    realtimeService_->setAddParamUploadChannelFunc(interface);
  }
}
