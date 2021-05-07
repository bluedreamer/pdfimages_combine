#pragma once

#include <filesystem>
#include <optional>
#include <ostream>
#include <string>

#include "Exceptions.h"
#include "ImageFileName.h"
#include "ImageReference.h"

/**
 * @class Represents a line from the output of pdfimages -list eg.
 * page   num  type   width height color comp bpc  enc interp  object ID x-ppi y-ppi size ratio
 * --------------------------------------------------------------------------------------------
 *    1     0 image    1226  1606  icc     4   8  jpeg   no      2033  0   145   145  315K 4.1%
 *    1     1 smask    2460  3223  gray    1   8  jpx    no      2033  0   290   290 12.5K 0.2%
 *
 */
class Entry
{
public:
   /**
    * Construct a Entry from text from file eg
    * "   1     0 image    1226  1606  icc     4   8  jpeg   no      2033  0   145   145  315K 4.1%"
    * @param line
    */
   explicit Entry(std::string line);

   /**
    * @enum Values in the "type" column
    */
   enum class ImageType
   {
      image_e,
      mask_e,
      smask_e,
      stencil_e
   };

   /**
    * @enum Values in the "color" column
    */
   enum class Colour
   {
      gray_e,    //< Gray
      rgb_e,     //< RGB
      cmyk_e,    //< CMYK
      lab_e,     //< L*a*b
      icc_e,     //< ICC Based
      index_e,   //< Indexed Color
      sep_e,     //< Separation
      devn_e,    //< DeviceN
      pattern_e, //< Pattern
   };

   /**
    * @enum Values in the "enc" column
    */
   enum class Encoding
   {
      ccitt_e, //< CCITT Group 3 or Group 4 Fax
      jpeg_e,  //< Joint Photographic Experts Group
      jpx_e,   //< JPEG2000
      jp2_e,   //< JPEG2000
      jbig2_e, //< Joint Bi-Level Image Experts Group
      image_e, //< raster image (may be Flate or LZW compressed but does not use an image encoding)
   };

   [[nodiscard]] auto getImageReference() const -> const ImageReference&;
   [[nodiscard]] auto isMask() const -> bool;
   [[nodiscard]] auto getNumber() const -> int;
   void               setFilename(std::optional<ImageFileName> filename);
   [[nodiscard]] auto compare(const Entry &entry) const -> bool;
   [[nodiscard]] auto getFilename() const -> const std::filesystem::path &;

   friend auto operator<<(std::ostream &os, const Entry &rhs) -> std::ostream &;

   static auto to_string(ImageType e) -> std::string;
   static auto to_string(Colour e) -> std::string;
   static auto to_string(Encoding e) -> std::string;
   template<typename Enum>
   static inline auto from_string(const std::string &str) -> Enum;
   static void        print_header(std::ostream &os);

private:
   void print(std::ostream &os) const;

   int            page_{-1};                 //< PDF page number image is on
   int            image_number_{-1};         //< Arbitrary int id, I think its order of appearence in the PDF
   ImageType      type_{ImageType::image_e}; //< Image type column
   int            width_{-1};                //< Image pixel width
   int            height_{-1};               //< Image pixel height
   Colour         colour_{Colour::gray_e};   //< Color type column
   int            colour_components_{-1};
   int            bits_per_component_{-1};
   Encoding       encoding_{Encoding::image_e}; //< Image encoding type
   bool           interpolation_{false};
   ImageReference image_reference_;
   //   int       image_reference_{-1};
   //   int                          object_generation_{-1};
   int                          x_ppi_{-1}; //< X Pixel Per Inch
   int                          y_ppi_{-1}; //< Y Pixel Per Inch
   std::string                  size_;      //< Human readable size eg "76.6K"
   std::string                  ratio_;     //< Compression ratio string eg "4.1%"
   std::optional<ImageFileName> filename_;  //< Matching filename on disk
};

template<>
inline auto Entry::from_string(const std::string &str) -> Entry::ImageType
{
   using namespace std::string_literals;
   ImageType imagetype;
   if(str == "image"s)
   {
      imagetype = ImageType::image_e;
   }
   else if(str == "mask"s)
   {
      imagetype = ImageType::mask_e;
   }
   else if(str == "smask"s)
   {
      imagetype = ImageType::smask_e;
   }
   else if(str == "stencil"s)
   {
      imagetype = ImageType::stencil_e;
   }
   else
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "Unknown image type: " << str;
   }

   return imagetype;
}

template<>
inline auto Entry::from_string(const std::string &str) -> Entry::Colour
{
   using namespace std::string_literals;
   Colour colour;
   if(str == "gray"s)
   {
      colour = Colour::gray_e;
   }
   else if(str == "rgb"s)
   {
      colour = Colour::rgb_e;
   }
   else if(str == "cmyk"s)
   {
      colour = Colour::cmyk_e;
   }
   else if(str == "lab"s)
   {
      colour = Colour::lab_e;
   }
   else if(str == "icc"s)
   {
      colour = Colour::icc_e;
   }
   else if(str == "index"s)
   {
      colour = Colour::index_e;
   }
   else if(str == "sep"s)
   {
      colour = Colour::sep_e;
   }
   else if(str == "devn"s)
   {
      colour = Colour::devn_e;
   }
   else if(str == "-"s)
   {
      colour = Colour::pattern_e;
   }
   else
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "Unknown Colour type: " << str;
   }

   return colour;
}

template<>
inline auto Entry::from_string(const std::string &str) -> Entry::Encoding
{
   using namespace std::string_literals;
   Encoding encoding;
   if(str == "image"s)
   {
      encoding = Encoding::image_e;
   }
   else if(str == "jpeg"s)
   {
      encoding = Encoding::jpeg_e;
   }
   else if(str == "jp2"s)
   {
      encoding = Encoding::jp2_e;
   }
   else if(str == "jbig2"s)
   {
      encoding = Encoding::jbig2_e;
   }
   else if(str == "ccitt"s)
   {
      encoding = Encoding::ccitt_e;
   }
   else if(str == "jpx"s)
   {
      encoding = Encoding::jpx_e;
   }
   else
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "Unknown Encoding type: " << str;
   }
   return encoding;
}
