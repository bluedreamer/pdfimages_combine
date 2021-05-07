#pragma once

#include "Entry.h"
#include <cstddef>
#include <map>

/**
 * @class Representation of the image on the page with its components as an image can appear multiple times in the document
 * and also have multiple parts
 */
class PdfImage
{
public:
   explicit PdfImage(ImageReference object_id);
   void               push_back(Entry entry);
   [[nodiscard]] auto size() const -> size_t;
   void               dump() const;
   void               printScript() const;

private:
   ImageReference       image_reference_;
   std::optional<Entry> first_one_;
   std::map<int, Entry> images_;
   std::map<int, Entry> smasks_;
};
