#pragma once

#include "IDataManagerExtension.h"

namespace DataManager::Mock {

struct DataManagerExtensionMock : public IDataManagerExtension {
  ParamUploadChannel* paramUploadChannel() override;
  void addParamUploadChannel(
      std::shared_ptr<ParamUploadChannel> channel) override;

  std::function<ParamUploadChannel*()> paramUploadChannel_;
  std::function<void(std::shared_ptr<ParamUploadChannel>)>
      addParamUploadChannel_;
};

}  // namespace DataManager::Mock
