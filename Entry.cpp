//
// Created by adrian on 2021-02-04.
//

#include "Entry.h"
#include <iomanip>
#include <sstream>

using namespace std::string_literals;

Entry::Entry(std::string line)
{
   std::istringstream strm(line);
   strm >> page_;
   strm >> image_number_;
   std::string temp;
   strm >> temp;
   if(temp == "image"s)
   {
      type_ = ImageType::image_e;
   }
   else if(temp == "mask"s)
   {
      type_ = ImageType::mask_e;
   }
   else if(temp == "smask"s)
   {
      type_ = ImageType::smask_e;
   }
   else if(temp == "stencil"s)
   {
      type_ = ImageType::stencil_e;
   }
   else
   {
      throw std::logic_error(temp + ": is unknown image type");
   }

   strm >> width_;
   strm >> height_;
   strm >> temp;
   if(temp == "gray"s)
   {
      colour_ = Colour::gray_e;
   }
   else if(temp == "rgb"s)
   {
      colour_ = Colour::rgb_e;
   }
   else if(temp == "cmyk"s)
   {
      colour_ = Colour::cmyk_e;
   }
   else if(temp == "lab"s)
   {
      colour_ = Colour::lab_e;
   }
   else if(temp == "icc"s)
   {
      colour_ = Colour::icc_e;
   }
   else if(temp == "index"s)
   {
      colour_ = Colour::index_e;
   }
   else if(temp == "sep"s)
   {
      colour_ = Colour::sep_e;
   }
   else if(temp == "devn"s)
   {
      colour_ = Colour::devn_e;
   }
   else
   {
      throw std::logic_error(temp + ": is unknown colour");
   }
   strm >> colour_components_;
   strm >> bits_per_component_;
   strm >> temp;
   if(temp == "image"s)
   {
      encoding_ = Encoding::image_e;
   }
   else if(temp == "jpeg"s)
   {
      encoding_ = Encoding::jpeg_e;
   }
   else if(temp == "jp2"s)
   {
      encoding_ = Encoding::jp2_e;
   }
   else if(temp == "jbig2"s)
   {
      encoding_ = Encoding::jbig2_e;
   }
   else if(temp == "ccitt"s)
   {
      encoding_ = Encoding::ccitt_e;
   }
   else
   {
      throw std::logic_error(temp + ": is unknown colour");
   }
   strm >> temp;
   if(temp == "no"s)
   {
      interpolation_ = false;
   }
   else if(temp == "yes"s)
   {
      interpolation_ = true;
   }
   else
   {
      throw std::logic_error(temp + ": is unknown interpolation");
   }
   strm >> object_id_;
   strm >> object_generation_;
   strm >> x_ppi_;
   strm >> y_ppi_;
   strm >> size_;
   strm >> ratio_;

   if(strm.bad())
   {
      throw std::logic_error("Stream bad. Not know do what?");
   }
}

int Entry::getObjectId() const
{
   return object_id_;
}

bool Entry::isMask() const
{
   if(type_ == ImageType::mask_e || type_ == ImageType::smask_e)
   {
      return true;
   }
   return false;
}

int Entry::getNumber() const
{
   return image_number_;
}
