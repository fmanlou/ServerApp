#pragma once

#include <memory>

#include "EcgConstants.h"
#include "ModuleExtension.h"
#include "Spo2Constants.h"

namespace Module {

std::shared_ptr<ModuleExtension> createEcgModuleExtension();

std::shared_ptr<ModuleExtension> createSpo2ModuleExtension();

}  // namespace Module