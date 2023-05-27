#pragma once

#include "CoreConstants.h"
#include "Data.h"
#include "Extension.h"

namespace Core {

class ICoreExtension : public Extension {
 public:
  ICoreExtension() : Extension(Constants::kCoreExtensionId) {}
  ~ICoreExtension() override = default;
  virtual void addParamProducer(ParamProducer producer) = 0;
};

}  // namespace Core