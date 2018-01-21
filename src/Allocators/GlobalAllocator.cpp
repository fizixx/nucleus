
#include "nucleus/Allocators/GlobalAllocator.h"

#include <cstdlib>

#include "nucleus/Config.h"

#include "nucleus/MemoryDebug.h"

namespace nu {

void* GlobalAllocator::doAllocate(USize bytes, USize alignment) {
#if COMPILER(MINGW)
  return ::malloc(bytes);
#elif COMPILER(GCC)
  void* result;
  ::posix_memalign(&result, alignment, bytes);
  return result;
#else   // COMPILER(GCC)
  return ::_aligned_malloc(bytes, alignment);
#endif  // COMPILER(GCC)
}

void GlobalAllocator::doFree(void* p, USize, USize) {
#if COMPILER(MSVC)
  ::_aligned_free(p);
#else
  ::free(p);
#endif
}

bool GlobalAllocator::doIsEqual(const Allocator& other) const noexcept {
  return this == &other;
}

}  // namespace nu
