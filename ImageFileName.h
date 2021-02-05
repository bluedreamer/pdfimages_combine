#pragma once

#include <filesystem>
#include <ostream>

class ImageFileName
{
public:
   explicit ImageFileName(std::filesystem::path filename);
   friend std::ostream& operator<<(std::ostream &os, const ImageFileName &rhs)
   {
      os << rhs.filename_;
      return os;
   }
   int getPageNumber() const { return page_number_; }
   int getImageNumber() const { return image_number_; }
   const   std::filesystem::path& getFilename() const { return filename_; }
private:
   std::filesystem::path filename_;
   int page_number_{0};
   int image_number_{0};
};


