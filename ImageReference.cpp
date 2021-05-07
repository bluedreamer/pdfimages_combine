#include "ImageReference.h"

ImageReference::ImageReference(int object_number, int generation_number)
   : object_number_(object_number)
   , generation_number_(generation_number)
{
}

auto ImageReference::getObjectNumber() const -> int
{
   return object_number_;
}

auto ImageReference::getGenerationNumber() const -> int
{
   return generation_number_;
}

auto operator==(const ImageReference &lhs, const ImageReference &rhs) -> bool
{
   return lhs.object_number_ == rhs.object_number_ && lhs.generation_number_ == rhs.generation_number_;
}

auto operator!=(const ImageReference &lhs, const ImageReference &rhs) -> bool
{
   return !(lhs == rhs);
}

auto operator<(const ImageReference &lhs, const ImageReference &rhs) -> bool
{
   if(lhs.object_number_ == rhs.object_number_)
   {
      return lhs.generation_number_ < rhs.generation_number_;
   }
   return lhs.object_number_ < rhs.object_number_;
}

auto operator<<(std::ostream &os, const ImageReference &rhs) -> std::ostream &
{
   os << rhs.object_number_ << ' ' << rhs.generation_number_;
   return os;
}
