#include <catch2/catch_all.hpp>

#include "RealtimeService.h"

struct RealtimeServiceTest {
  RealtimeServiceTest() {
    service_ = std::make_unique<RealtimeService>();
    service_->setWriterHelper(nullptr);
  }

  void testCheckParamStrategy() {
    service_->stop();
    REQUIRE(service_->sendValue(nullptr, nullptr, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->sendValue(&context_, nullptr, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(
        service_->sendValue(nullptr, &emptyRequest_, nullptr).error_code() ==
        grpc::StatusCode::CANCELLED);
    REQUIRE(
        service_->sendValue(&context_, &emptyRequest_, nullptr).error_code() ==
        grpc::StatusCode::CANCELLED);
  }

  void testSendValue() {
    Param data{1, 1};
    auto interface = [&](std::shared_ptr<ParamUploadChannel> channel) {
      queue_.addChannel(channel);
      queue_.upload(data);
    };
    service_->setAddParamUploadChannelFunc(interface);
    auto mockHelper = [this, &data](grpc::ServerWriter<data::Value> *writer,
                                    const data::Value &value) {
      REQUIRE(value.index() == data.index);
      REQUIRE(value.value() == data.value);
      service_->stop();
    };
    auto strategy = [](grpc::ServerWriter<data::Value> *writer) {
      return true;
    };
    service_->setWriterHelper(mockHelper);
    service_->setCheckWritertrategy(strategy);
    service_->sendValue(&context_, &emptyRequest_, nullptr);
  }

  void testGetIdNullptr() {
    data::Index index;
    data::Id id;

    REQUIRE(service_->getId(nullptr, nullptr, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(&context_, nullptr, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(nullptr, &index, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(nullptr, nullptr, &id).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(&context_, &index, nullptr).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(&context_, nullptr, &id).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(nullptr, &index, &id).error_code() ==
            grpc::StatusCode::CANCELLED);
    REQUIRE(service_->getId(&context_, &index, &id).error_code() ==
            grpc::StatusCode::CANCELLED);
  }

  void testGetId() {
    MetaParam param{"1", 1};

    service_->registerMetaParam(param);

    data::Index request;
    request.set_index(param.index);

    data::Id response;
    service_->getId(&context_, &request, &response);

    REQUIRE(response.id() == param.id);
  }

  void testSetCheckParamsStrategy() {
    service_->setCheckWritertrategy(nullptr);
    REQUIRE(
        service_->sendValue(&context_, &emptyRequest_, nullptr).error_code() ==
        grpc::StatusCode::CANCELLED);
  }

  void testAddParamUploadChannelInterface() {
    service_->setAddParamUploadChannelFunc(nullptr);
    REQUIRE(
        service_->sendValue(&context_, &emptyRequest_, nullptr).error_code() ==
        grpc::StatusCode::CANCELLED);
  }

  std::unique_ptr<RealtimeService> service_;
  grpc::ServerContext context_;
  data::Empty emptyRequest_;
  TransferChannel<Param> queue_;
};

TEST_CASE_METHOD(RealtimeServiceTest, "[RealtimeService]") {
  SECTION("testCheckParamStrategy") { testCheckParamStrategy(); }
  SECTION("testGetIdNullptr") { testGetIdNullptr(); }
  SECTION("testGetId") { testGetId(); }
  SECTION("testSendValue") { testSendValue(); }
  SECTION("testAddParamUploadChannelInterface") {
    testAddParamUploadChannelInterface();
  }
}