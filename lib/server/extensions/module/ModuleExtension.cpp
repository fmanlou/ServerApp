#include "ModuleExtension.h"

#include "CoreConstants.h"
#include "CoreExtension.h"
#include "ExtensionManager.h"
#include "IServerExtension.h"
#include "LoopIncParamProducer.h"

namespace Module {

ModuleExtension::ModuleExtension(const std::string& id, MetaParam metaParam,
                                 const MetaLoopIncParam& metaLoopIncParam)
    : Extension(id),
      metaParam_(metaParam),
      metaLoopIncParam_(metaLoopIncParam) {}

void ModuleExtension::initialize(IExtensionManager& manager) {
  auto grpcExtension =
      manager.getExtension<IServerExtension>(kGrpcServerExtensionId);
  if (grpcExtension) {
    grpcExtension->registerMetaParam(metaParam_);
  }

  auto coreExtension = manager.getExtension<Core::ICoreExtension>(
      Core::Constants::kCoreExtensionId);
  if (coreExtension) {
    coreExtension->addParamProducer(LoopIncParamProducer(metaLoopIncParam_));
  }
}

}  // namespace Module
