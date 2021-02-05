#include "Entry.h"
#include "Exceptions.h"
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
   type_ = from_string<ImageType>(temp);

   strm >> width_;
   strm >> height_;
   strm >> temp;
   colour_ = from_string<Colour>(temp);
   strm >> colour_components_;
   strm >> bits_per_component_;
   strm >> temp;
   encoding_ = from_string<Encoding>(temp);

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
      throw LogicError(__FILE__, __func__, __LINE__) << "Unknown interpolation: " << temp;
   }
   strm >> object_id_;
   strm >> object_generation_;
   strm >> x_ppi_;
   strm >> y_ppi_;
   strm >> size_;
   strm >> ratio_;

   if(strm.bad())
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "Unabled to parse: [" << line << "]";
   }
}

auto Entry::getObjectId() const -> int
{
   return object_id_;
}

auto Entry::isMask() const -> bool
{
   if(type_ == ImageType::mask_e || type_ == ImageType::smask_e)
   {
      return true;
   }
   return false;
}

auto Entry::getNumber() const -> int
{
   return image_number_;
}

void Entry::setFilename(std::optional<ImageFileName> filename)
{
   if(filename)
   {
      if(filename->getPageNumber() != page_ || filename->getImageNumber() != image_number_)
      {
         throw LogicError(__FILE__, __func__, __LINE__) << "Filename: " << filename->getFilename() << " doesnt match "
                                                        << "page=" << page_ << " imagenum=" << image_number_;
      }
      filename_ = filename;
   }
}

auto Entry::to_string(ImageType e) -> std::string
{
   switch(e)
   {
      case ImageType::image_e:
         return "image"s;
      case ImageType::mask_e:
         return "mask"s;
      case ImageType::smask_e:
         return "smask"s;
      case ImageType::stencil_e:
         return "stencil"s;
   }
   throw LogicError(__FILE__, __func__, __LINE__) << "Cannot convert ImageType to string: " << (int)e;
}

auto Entry::to_string(Colour e) -> std::string
{
   switch(e)
   {
      case Colour::gray_e:
         return "gray"s;
      case Colour::rgb_e:
         return "rgb"s;
      case Colour::cmyk_e:
         return "cmyk"s;
      case Colour::lab_e:
         return "lab"s;
      case Colour::icc_e:
         return "icc"s;
      case Colour::index_e:
         return "index"s;
      case Colour::sep_e:
         return "sep"s;
      case Colour::devn_e:
         return "devn"s;
   }
   throw LogicError(__FILE__, __func__, __LINE__) << "Cannot convert Colour to string: " << (int)e;
}

auto Entry::to_string(Encoding e) -> std::string
{
   switch(e)
   {
      case Encoding::image_e:
         return "image"s;
      case Encoding::jpeg_e:
         return "jpeg"s;
      case Encoding::jp2_e:
         return "jp2"s;
      case Encoding::jbig2_e:
         return "jbig2"s;
      case Encoding::ccitt_e:
         return "ccitt"s;
   }
   throw LogicError(__FILE__, __func__, __LINE__) << "Cannot convert Encoding to string: " << (int)e;
}

void Entry::print_header(std::ostream &os)
{
   os << "page   num  type   width height color comp bpc  enc interp  object ID x-ppi y-ppi size ratio\n";
   os << "--------------------------------------------------------------------------------------------\n";
}

void Entry::print(std::ostream &os) const
{
   os << std::setw(4) << page_ << ' ';
   os << std::setw(5) << image_number_ << ' ';
   os << std::setw(7) << to_string(type_) << ' ';
   os << std::setw(5) << width_ << ' ';
   os << std::setw(5) << height_ << ' ';
   os << std::setw(5) << to_string(colour_) << ' ';
   os << std::setw(4) << colour_components_ << ' ';
   os << std::setw(4) << bits_per_component_ << ' ';
   os << std::setw(5) << to_string(encoding_) << ' ';
   os << std::setw(3) << (interpolation_ ? "yes" : "no") << ' ';
   os << std::setw(7) << object_id_ << ' ';
   os << std::setw(1) << object_generation_ << ' ';
   os << std::setw(5) << x_ppi_ << ' ';
   os << std::setw(5) << y_ppi_ << ' ';
   os << std::setw(5) << size_ << ' ';
   os << std::setw(4) << ratio_ << ' ';
   if(filename_)
   {
      os << filename_.value();
   }
}

auto operator<<(std::ostream &os, const Entry &rhs) -> std::ostream &
{
   rhs.print(os);
   return os;
}

auto Entry::compare(const Entry &entry) const -> bool
{
   if(width_ != entry.width_)
   {
      return false;
   }
   if(height_ != entry.height_)
   {
      return false;
   }
   //   if(x_ppi_ != entry.x_ppi_)
   //   {
   //      return false;
   //   }
   //   if(y_ppi_ != entry.y_ppi_)
   //   {
   //      return false;
   //   }
   return true;
}
auto Entry::getFilename() const -> const std::filesystem::path &
{
   if(!filename_)
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "No filename set for entry!! " << *this;
   }

   return filename_->getFilename();
}
