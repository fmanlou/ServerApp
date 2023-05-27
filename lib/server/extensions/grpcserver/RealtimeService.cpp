#include "RealtimeService.h"

#include <thread>

#include "QueueBiChannel.h"

using data::Empty;
using data::Value;
using grpc::ServerContext;
using grpc::Status;

bool checkWriter(grpc::ServerWriter<data::Value> *writer) { return writer; }

void writerHelper(grpc::ServerWriter<data::Value> *writer,
                  const data::Value &data) {
  writer->Write(data);
}

RealtimeService::RealtimeService() {
  writerHelper_ = writerHelper;
  checkWriterStrategy_ = checkWriter;
}

Status RealtimeService::sendValue(ServerContext *context, const Empty *request,
                                  grpc::ServerWriter<Value> *writer) {
  if (!context || !request || !checkWriterStrategy_ ||
      !checkWriterStrategy_(writer) || addParamUploadChannel_ == nullptr) {
    return Status::CANCELLED;
  }

  Value value;
  Param data;
  auto channel = std::make_shared<QueueBiChannel<Param>>();

  addParamUploadChannel_(channel);

  while (running_ && !context->IsCancelled()) {
    if (channel->timeWaitAnddownload(data, std::chrono::milliseconds(100))) {
      value.set_index(data.index);
      value.set_value(data.value);
      if (writerHelper_) writerHelper_(writer, value);
    }
  }

  return Status::OK;
}

grpc::Status RealtimeService::getId(::grpc::ServerContext *context,
                                    const ::data::Index *request,
                                    ::data::Id *response) {
  if (!response || !context || !request) {
    return Status::CANCELLED;
  }

  if (metaParamMap_.find(request->index()) == metaParamMap_.end()) {
    return Status::CANCELLED;
  }

  response->set_id(metaParamMap_[request->index()].id);

  return Status::OK;
}

void RealtimeService::setWriterHelper(ServerWriterHelper helper) {
  writerHelper_ = helper;
}

void RealtimeService::setCheckWritertrategy(CheckWriterStrategy strategy) {
  checkWriterStrategy_ = strategy;
}

void RealtimeService::registerMetaParam(const MetaParam &param) {
  metaParamMap_[param.index] = param;
}

void RealtimeService::stop() { running_ = false; }

void RealtimeService::setAddParamUploadChannelFunc(
    AddParamUploadChannelFunc addParamUploadChannel) {
  addParamUploadChannel_ = addParamUploadChannel;
}
