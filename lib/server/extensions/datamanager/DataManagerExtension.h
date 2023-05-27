#pragma once

#include "IDataManagerExtension.h"
#include "TransferChannel.h"

namespace DataManager {

class DataManagerExtension : public IDataManagerExtension {
 public:
  ParamUploadChannel* paramUploadChannel() override;
  void addParamUploadChannel(
      std::shared_ptr<ParamUploadChannel> channel) override;

 private:
  TransferChannel<Param> paramTransferChannel_;
};

}  // namespace DataManager
