#pragma once

#include "Data.h"
#include "Extension.h"
#include "IExtensionManager.h"
#include "MetaLoopIncParam.h"

namespace Module {

class ModuleExtension : public Extension {
 public:
  explicit ModuleExtension(const std::string& id, MetaParam metaParam,
                           const MetaLoopIncParam& metaLoopIncParam);
  void initialize(IExtensionManager& manager) override;

 private:
  const MetaParam metaParam_;
  const MetaLoopIncParam metaLoopIncParam_;
  ;
};

}  // namespace Module
