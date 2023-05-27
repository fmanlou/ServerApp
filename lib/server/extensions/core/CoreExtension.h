#pragma once

#include "BlockingQueue.h"
#include "Data.h"
#include "DataManagerExtension.h"
#include "Extension.h"
#include "ICoreExtension.h"
#include "TaskScheduler.h"

namespace Core {

using DataManager::ParamUploadChannel;

class CoreExtension : public ICoreExtension {
 public:
  ~CoreExtension() override;
  void initialize(IExtensionManager& manager) override;
  void addParamProducer(ParamProducer producer) override;

 private:
  void produceAndUploadParam(ParamUploadChannel& uploadChannel);

 private:
  std::vector<ParamProducer> producers_;
  std::jthread producerThread_;
  std::mutex mutex_;
};

}  // namespace Core
