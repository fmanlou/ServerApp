#pragma once

#include <functional>

#include "ICoreExtension.h"

namespace Core::Mock {

struct CoreExtensionMock : public ICoreExtension {
  void addParamProducer(ParamProducer producer) override;

  std::function<void(ParamProducer)> addParamProducer_;
};

};  // namespace Core::Mock
