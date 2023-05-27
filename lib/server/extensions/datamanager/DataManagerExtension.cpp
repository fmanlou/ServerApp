#include "DataManagerExtension.h"

namespace DataManager {

ParamUploadChannel* DataManagerExtension::paramUploadChannel() {
  return &paramTransferChannel_;
}

void DataManagerExtension::addParamUploadChannel(
    std::shared_ptr<ParamUploadChannel> channel) {
  paramTransferChannel_.addChannel(channel);
}

}  // namespace DataManager
