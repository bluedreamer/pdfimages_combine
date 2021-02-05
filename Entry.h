#pragma once

#include <string>

class Entry
{
public:
   explicit Entry(std::string line);
   enum class ImageType
   {
      image_e,
      mask_e,
      smask_e,
      stencil_e
   };
   enum class Colour
   {
      gray_e,  //<  Gray
      rgb_e,   //<  RGB
      cmyk_e,  //< CMYK
      lab_e,   //< L*a*b
      icc_e,   //< ICC Based
      index_e, //< Indexed Color
      sep_e,   //<  Separation
      devn_e,  //< DeviceN
   };
   enum class Encoding
   {
      image_e, //< raster image (may be Flate or LZW compressed but does not use an image encoding)
      jpeg_e,  //< Joint Photographic Experts Group
      jp2_e,   //< JPEG2000
      jbig2_e, //< Joint Bi-Level Image Experts Group
      ccitt_e, //< CCITT Group 3 or Group 4 Fax
   };

   int  getObjectId() const;
   bool isMask() const;
   int  getNumber() const;

private:
   int         page_{-1};
   int         image_number_{-1};
   ImageType   type_{ImageType::image_e};
   int         width_{-1};
   int         height_{-1};
   Colour      colour_{Colour::gray_e};
   int         colour_components_{-1};
   int         bits_per_component_{-1};
   Encoding    encoding_{Encoding::image_e};
   bool        interpolation_{false};
   int         object_id_{-1};
   int         object_generation_{-1};
   int         x_ppi_{-1};
   int         y_ppi_{-1};
   std::string size_;
   std::string ratio_;
};
