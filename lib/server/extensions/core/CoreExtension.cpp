#include "CoreExtension.h"

#include "CoreConstants.h"
#include "DataManagerConstants.h"
#include "IExtensionManager.h"

namespace Core {

CoreExtension::~CoreExtension() {
  producerThread_.request_stop();
  if (producerThread_.joinable()) {
    producerThread_.join();
  }
}

void CoreExtension::initialize(IExtensionManager& manager) {
  auto dataManagerExtension =
      manager.getExtension<DataManager::IDataManagerExtension>(
          DataManager::Constants::kDataManagerExtensionId);
  DataManager::ParamUploadChannel* uploadChannel = nullptr;
  if (dataManagerExtension) {
    uploadChannel = dataManagerExtension->paramUploadChannel();
  }

  auto task = [this, uploadChannel](std::stop_token token) {
    if (uploadChannel == nullptr) return;
    while (!token.stop_requested()) {
      produceAndUploadParam(*uploadChannel);
      sleep(1);
    }
  };
  producerThread_ = std::jthread(task);
}

void CoreExtension::addParamProducer(ParamProducer producer) {
  std::lock_guard<std::mutex> lock(mutex_);
  producers_.push_back(producer);
}

void CoreExtension::produceAndUploadParam(ParamUploadChannel& uploadChannel) {
  std::lock_guard<std::mutex> lock(mutex_);
  for (auto& producer : producers_) {
    if (producer) uploadChannel.upload(producer());
  }
}

}  // namespace Core