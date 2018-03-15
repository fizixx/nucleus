
#ifndef NUCLEUS_MEMORY_REF_COUNTED_H_
#define NUCLEUS_MEMORY_REF_COUNTED_H_

#include <atomic>

#include "nucleus/Macros.h"

namespace nu {

namespace detail {

class RefCountedBase {
public:
  COPY_DELETE(RefCountedBase);
  MOVE_DELETE(RefCountedBase);

  bool hasOneRef() const {
    return m_refCount.load(std::memory_order_release) == 1;
  }

  void addRef() const {
    m_refCount.fetch_add(1, std::memory_order_relaxed);
  }

  bool release() const {
    return m_refCount.fetch_sub(1, std::memory_order_release) == 1;
  }

protected:
  RefCountedBase() = default;
  ~RefCountedBase() = default;

private:
  mutable std::atomic<USize> m_refCount{};
};

template <typename T>
struct DefaultRefCountedTraits {
  static void destruct(const T*) {}
};

}  // namespace detail

template <typename T, typename Traits = detail::DefaultRefCountedTraits<T>>
class RefCounted : public detail::RefCountedBase {
public:
  void addRef() const {
    detail::RefCountedBase::addRef();
  }

  void release() const {
    if (detail::RefCountedBase::release()) {
      Traits::destruct(static_cast<const T*>(this));
    }
  }
};

}  // namespace nu

#endif  // NUCLEUS_MEMORY_REF_COUNTED_H_
