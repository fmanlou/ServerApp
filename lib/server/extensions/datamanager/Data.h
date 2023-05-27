#pragma once

#include <functional>
#include <string>

struct Param {
  int index;
  int value;

  bool operator==(const Param& other) const {
    return index == other.index && value == other.value;
  }

  bool operator!=(const Param& other) const { return !(*this == other); }
};

struct MetaParam {
  std::string id;
  int index;

  bool operator==(const MetaParam& other) const {
    return id == other.id && index == other.index;
  }

  bool operator!=(const MetaParam& other) const { return !(*this == other); }
};

using ParamProducer = std::function<Param()>;
