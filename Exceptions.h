#pragma once

#include "streaming_exception/StreamingException.h"

// Because you wont remember this later
// Dont do
// throw LogicError() << "blah"
// because it gets sliced to base unless you redefine operator<<
class LogicError : public StreamingException
{
public:
   using StreamingException::StreamingException;
   template<typename T>
   auto operator<<(const T &value) noexcept -> LogicError &
   {
      StreamingException::operator<<(value);
      return *this;
   }
};
