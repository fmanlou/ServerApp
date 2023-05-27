#pragma once

#include "Data.h"
#include "MetaLoopIncParam.h"

namespace Ecg::Constants {

constexpr char kEcgExtensionId[] = "ecg";
constexpr char kHrParamId[] = "HR";
constexpr int kHrParamIndex = 1;
constexpr int kUpper = 120;
constexpr int kLower = 50;
const MetaParam kHrParam = {kHrParamId, kHrParamIndex};
constexpr MetaLoopIncParam kHrParamData = {kHrParamIndex, kLower, kUpper};

}  // namespace Ecg::Constants
