#include <catch2/catch_all.hpp>

#include "QueueBiChannel.h"
#include "TransferChannel.h"

struct TransferChannelTest {
  void testUploadHelper() {
    std::vector<std::shared_ptr<IUploadChannel<int>>> channels;
    channels.push_back(std::make_shared<QueueBiChannel<int>>());
    channels.push_back(nullptr);
    uploadHelper(channels, 1);
    REQUIRE(channels.size() == 1);
  }
};

TEST_CASE_METHOD(TransferChannelTest, "[TransferChannel]") {
  SECTION("testUploadHelper") { testUploadHelper(); }
}