#include "PdfImage.h"
#include "Exceptions.h"

#include <iostream>

PdfImage::PdfImage(int object_id)
   : object_id_(object_id)
{
}

void PdfImage::push_back(Entry e)
{
   if(e.getObjectId() != object_id_)
   {
      throw LogicError(__FILE__, __func__, __LINE__)
         << "Trying to add Entry with id: " << e.getObjectId() << " to this which has id: " << object_id_;
   }

   if(!first_one_)
   {
      first_one_ = e; // copy because its moved after
   }
   else
   {
      if(!first_one_.value().compare(e))
      {
         throw LogicError(__FILE__, __func__, __LINE__) << "Adding Entry that doesn't match key fields, incoming:\n"
                                                        << e << "\nvs existing\n"
                                                        << first_one_.value();
      }
   }

   auto file_number = e.getNumber();
   if(e.isMask())
   {
      auto result = smasks_.emplace(std::make_pair(file_number, std::move(e)));
      if(!result.second)
      {
         throw LogicError(__FILE__, __func__, __LINE__) << "Failed to insert mask entry: " << e;
      }
   }
   else
   {
      auto result = images_.emplace(std::make_pair(file_number, std::move(e)));
      if(!result.second)
      {
         throw LogicError(__FILE__, __func__, __LINE__) << "Failed to insert image entry:\n" << e << '\n' << result.first->second;
      }
   }
}

auto PdfImage::size() const -> size_t
{
   return images_.size() + smasks_.size();
}

void PdfImage::dump() const
{
   std::cout << "\nObject ID: " << object_id_ << std::endl;
   if(!images_.empty())
   {
      std::cout << "Images:\n";
      Entry::print_header(std::cout);
      for(const auto &[filenumber, entry] : images_)
      {
         std::cout << entry << std::endl;
      }
   }
   if(!smasks_.empty())
   {
      std::cout << "Masks:\n";
      Entry::print_header(std::cout);
      for(const auto &[filenumber, entry] : smasks_)
      {
         std::cout << entry << std::endl;
      }
   }
}
void PdfImage::printScript() const
{
   for(const auto &[number, entry] : images_)
   {
      auto        mask     = smasks_.find(entry.getNumber() + 1);
      const auto &filename = entry.getFilename();
      auto        output   = std::filesystem::path("output/");
      std::filesystem::create_directory(output);
      output += filename.stem();
      output += "-";
      output += std::to_string(object_id_);
      if(mask == smasks_.end())
      {
         output += filename.extension();
         std::cout << "convert -strip " << filename << " " << output << std::endl;
         //         std::cout << "rm " << filename << std::endl;
      }
      else
      {
         output += ".png";
         std::cout << "composite -strip -compose CopyOpacity " << mask->second.getFilename() << " " << filename << " " << output
                   << std::endl;
         //         std::cout << "rm " << mask->second.getFilename() << " " << filename << std::endl;
      }
   }
}
