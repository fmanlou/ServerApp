#pragma once

#include <functional>

#include "IServerExtension.h"

struct ServerExtensionMock : public IServerExtension {
  void build(const std::string& address) override;
  void wait() override;
  void shutdown() override;
  void registerMetaParam(const MetaParam& param) override;

  std::function<void(const std::string&)> build_;
  std::function<void()> wait_;
  std::function<void()> shutdown_;
  std::function<void(const MetaParam&)> registerMetaParam_;
};
