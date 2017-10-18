
#include "nucleus/streams/wrapped_memory_input_stream.h"

#include <algorithm>
#include <cstring>

#include "nucleus/logging.h"
#include "nucleus/types.h"

namespace nu {

WrappedMemoryInputStream::WrappedMemoryInputStream(const void* data, USize size) : m_data(data), m_size(size) {}

WrappedMemoryInputStream::WrappedMemoryInputStream(const std::vector<char>& data)
  : m_data(data.data()), m_size(data.size()) {}

WrappedMemoryInputStream::SizeType WrappedMemoryInputStream::getLength() {
  return m_size;
}

WrappedMemoryInputStream::SizeType WrappedMemoryInputStream::read(void* buffer, SizeType bytesToRead) {
  DCHECK(bytesToRead >= 0);

  SizeType num = std::min(bytesToRead, getBytesRemaining());

  std::memcpy(buffer, static_cast<const U8*>(m_data) + m_currentPosition, static_cast<USize>(num));
  m_currentPosition += num;

  return num;
}

bool WrappedMemoryInputStream::isExhausted() {
  return m_currentPosition >= m_size;
}

bool WrappedMemoryInputStream::setPosition(SizeType newPosition) {
  m_currentPosition = std::max(newPosition, static_cast<SizeType>(0));
  m_currentPosition = std::min(newPosition, m_size);
  return true;
}

WrappedMemoryInputStream::SizeType WrappedMemoryInputStream::getPosition() {
  return m_currentPosition;
}

}  // namespace nu
