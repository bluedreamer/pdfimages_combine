#pragma once

#include <filesystem>
#include <ostream>

class ImageFileName
{
public:
   explicit ImageFileName(std::filesystem::path filename);
   friend auto operator<<(std::ostream &os, const ImageFileName &rhs) -> std::ostream &
   {
      os << rhs.filename_;
      return os;
   }
   [[nodiscard]] auto getPageNumber() const -> int { return page_number_; }
   [[nodiscard]] auto getImageNumber() const -> int { return image_number_; }
   [[nodiscard]] auto getFilename() const -> const std::filesystem::path & { return filename_; }

private:
   std::filesystem::path filename_;
   int                   page_number_{0};
   int                   image_number_{0};
};
