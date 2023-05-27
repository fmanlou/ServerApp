#include "Extension.h"

#include "IExtensionManager.h"

Extension::Extension(const std::string& id) : id_(id) {}

std::string Extension::id() { return id_; }

void Extension::initialize(IExtensionManager& manager) {}
