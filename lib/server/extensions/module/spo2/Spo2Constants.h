#pragma once

#include "Data.h"
#include "MetaLoopIncParam.h"

namespace Spo2::Constants {

constexpr char kSpo2ExtensionId[] = "spo2";
constexpr char kSpo2ParamId[] = "SPO2";
constexpr int kSpo2ParamIndex = 2;
constexpr int kUpper = 100;
constexpr int kLower = 80;
const MetaParam kSpo2Param = {kSpo2ParamId, kSpo2ParamIndex};
constexpr MetaLoopIncParam kSpo2ParamData = {kSpo2ParamIndex, kLower, kUpper};

}  // namespace Spo2::Constants