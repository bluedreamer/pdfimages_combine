#pragma once

#include "Entry.h"
#include <cstddef>
#include <map>

class PdfImage
{
public:
   explicit PdfImage(int object_id);
   void                 push_back(Entry e);
   [[nodiscard]] size_t size() const;
   void                 dump() const;
   void                 printScript() const;

private:
   int                  object_id_;
   std::optional<Entry> first_one_;
   std::map<int, Entry> images_;
   std::map<int, Entry> smasks_;
};
