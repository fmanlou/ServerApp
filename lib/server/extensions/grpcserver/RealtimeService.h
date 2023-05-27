#pragma once

#include <memory>

#include "Data.h"
#include "DataManagerExtension.h"
#include "data.grpc.pb.h"
#include "service.grpc.pb.h"

using DataManager::ParamUploadChannel;
using ServerWriterHelper = std::function<void(
    grpc::ServerWriter<data::Value>* writer, const data::Value& data)>;
using CheckWriterStrategy =
    std::function<bool(grpc::ServerWriter<data::Value>* writer)>;
using AddParamUploadChannelFunc =
    std::function<void(std::shared_ptr<ParamUploadChannel> channel)>;

class RealtimeService final : public data::RealtimeService::Service {
 public:
  RealtimeService();
  grpc::Status sendValue(grpc::ServerContext* context,
                         const data::Empty* request,
                         grpc::ServerWriter<data::Value>* writer) override;
  grpc::Status getId(::grpc::ServerContext* context,
                     const ::data::Index* request,
                     ::data::Id* response) override;
  void setWriterHelper(ServerWriterHelper helper);
  void setCheckWritertrategy(CheckWriterStrategy strategy);
  void registerMetaParam(const MetaParam& param);
  void stop();
  void setAddParamUploadChannelFunc(
      AddParamUploadChannelFunc addParamUploadChannel);

 private:
  std::unordered_map<int, MetaParam> metaParamMap_;
  AddParamUploadChannelFunc addParamUploadChannel_;
  ServerWriterHelper writerHelper_;
  CheckWriterStrategy checkWriterStrategy_;
  bool running_{true};
};
