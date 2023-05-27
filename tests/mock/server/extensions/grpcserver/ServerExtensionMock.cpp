#include "ServerExtensionMock.h"

void ServerExtensionMock::build(const std::string &address) {
  if (build_) build_(address);
}

void ServerExtensionMock::wait() {
  if (wait_) wait_();
}

void ServerExtensionMock::shutdown() {
  if (shutdown_) shutdown_();
}

void ServerExtensionMock::registerMetaParam(const MetaParam &param) {
  if (registerMetaParam_) registerMetaParam_(param);
}
