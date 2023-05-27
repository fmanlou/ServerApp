#pragma once

#include <array>

namespace Disruptor {

template <typename T, std::size_t N>
class RingBuffer {
 public:
  static_assert(((N > 0) && ((N & (~N + 1)) == N)),
                "RingBuffer's size must be a positive power of 2");

  T& operator[](const int64_t& sequence) { return buffer_[sequence & (N - 1)]; }

 private:
  std::array<T, N> buffer_;
};

}  // namespace Disruptor
