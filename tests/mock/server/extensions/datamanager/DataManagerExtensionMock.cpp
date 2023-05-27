#include "DataManagerExtensionMock.h"

namespace DataManager::Mock {

ParamUploadChannel* DataManagerExtensionMock::paramUploadChannel() {
  if (paramUploadChannel_) return paramUploadChannel_();
  return nullptr;
}

void DataManagerExtensionMock::addParamUploadChannel(
    std::shared_ptr<ParamUploadChannel> channel) {
  if (addParamUploadChannel_) addParamUploadChannel_(channel);
}

}  // namespace DataManager::Mock
