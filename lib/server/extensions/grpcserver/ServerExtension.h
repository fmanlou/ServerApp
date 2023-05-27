#pragma once

#include <grpcpp/grpcpp.h>

#include <memory>

#include "IExtensionManager.h"
#include "IServerExtension.h"
#include "RealtimeService.h"

class ServerExtension : public IServerExtension {
 public:
  ServerExtension();
  void build(const std::string& address) override;
  void wait() override;
  void shutdown() override;
  void registerMetaParam(const MetaParam& param) override;
  void initialize(IExtensionManager& manager) override;

 private:
  std::unique_ptr<grpc::Server> server_;
  std::unique_ptr<RealtimeService> realtimeService_;
};