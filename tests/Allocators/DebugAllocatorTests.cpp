
#if 0
#include "nucleus/Allocators/DebugAllocator.h"
#include <catch2.hpp>void expectDebugValues(const nu::DebugAllocator& debug, MemSize bytesAllocated,
                       MemSize bytesFreed) {
  CHECK(debug.getBytesAllocated() == bytesAllocated);
  CHECK(debug.getBytesFreed() == bytesFreed);
}

TEST_CASE("allocate from debug allocator", "[Allocators]") {
  nu::GlobalAllocator global;
  nu::DebugAllocator debug{&global};

  void* p1 = debug.allocate(16, 16);
  expectDebugValues(debug, 16, 0);

  debug.free(p1, 16, 16);
  expectDebugValues(debug, 16, 16);
}
#endif  // 0
