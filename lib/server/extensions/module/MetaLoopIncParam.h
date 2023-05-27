#pragma once

struct MetaLoopIncParam {
  int index;
  int lower;
  int upper;

  bool operator==(const MetaLoopIncParam& other) const {
    return index == other.index && lower == other.lower && upper == other.upper;
  }

  bool operator!=(const MetaLoopIncParam& other) const {
    return !(*this == other);
  }
};