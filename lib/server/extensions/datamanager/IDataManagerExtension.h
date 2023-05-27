#pragma once

#include <memory>

#include "Data.h"
#include "DataManagerConstants.h"
#include "Extension.h"
#include "IDownloadChannel.h"
#include "IUploadChannel.h"

namespace DataManager {

using ParamUploadChannel = IUploadChannel<Param>;
using ParamDownloadChannel = IDownloadChannel<Param>;

class IDataManagerExtension : public Extension {
 public:
  IDataManagerExtension() : Extension(Constants::kDataManagerExtensionId) {}
  virtual ~IDataManagerExtension() = default;
  virtual ParamUploadChannel* paramUploadChannel() = 0;
  virtual void addParamUploadChannel(
      std::shared_ptr<ParamUploadChannel> channel) = 0;
};

}  // namespace DataManager
