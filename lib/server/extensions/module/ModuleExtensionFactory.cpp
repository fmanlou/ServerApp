#include "ModuleExtensionFactory.h"

namespace Module {

std::shared_ptr<ModuleExtension> createEcgModuleExtension() {
  return std::make_shared<ModuleExtension>(Ecg::Constants::kEcgExtensionId,
                                           Ecg::Constants::kHrParam,
                                           Ecg::Constants::kHrParamData);
}

std::shared_ptr<ModuleExtension> createSpo2ModuleExtension() {
  return std::make_shared<ModuleExtension>(Spo2::Constants::kSpo2ExtensionId,
                                           Spo2::Constants::kSpo2Param,
                                           Spo2::Constants::kSpo2ParamData);
}

}  // namespace Module