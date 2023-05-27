#pragma once

#include <memory>

#include "Data.h"
#include "Extension.h"
#include "GrpcServerConstants.h"

class IServerExtension : public Extension {
 public:
  IServerExtension() : Extension(kGrpcServerExtensionId) {}
  virtual ~IServerExtension() = default;
  virtual void build(const std::string& address) = 0;
  virtual void shutdown() = 0;
  virtual void wait() = 0;
  virtual void registerMetaParam(const MetaParam& param) = 0;
};
