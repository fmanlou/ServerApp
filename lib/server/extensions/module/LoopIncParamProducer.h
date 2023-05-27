#pragma once

#include "Data.h"
#include "MetaLoopIncParam.h"

class LoopIncParamProducer {
 public:
  LoopIncParamProducer(const MetaLoopIncParam& data)
      : data_(data), value_(data.lower) {}

  Param operator()() {
    value_ = bound(value_, data_.lower, data_.upper);
    return {data_.index, value_++};
  }

  const MetaLoopIncParam& data() { return data_; }

  static int bound(int value, int lower, int upper) {
    return value > upper ? lower : value;
  }

 private:
  MetaLoopIncParam data_;
  int value_{0};
};