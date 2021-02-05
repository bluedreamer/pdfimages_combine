#include "ImageContainer.h"
#include "Entry.h"
#include "FileList.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

ImageContainer::ImageContainer(std::string prefix, std::string filename)
   : prefix_(prefix)
   , filelist_(".", prefix)
{
   std::ifstream in(filename.c_str());
   int           lineno = 0;
   std::string   line;

   while(std::getline(in, line))
   {
      // std::cout << line << std::endl;
      ++lineno;
      if(lineno < 3)
      {
         continue;
      }

      Entry entry(line);
      push_back(entry);
   }

   if(images_.empty())
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "No entries read from pdfimages -list output file: " << filename;
   }
}

void ImageContainer::push_back(Entry e)
{
   auto id = e.getObjectId();
   auto i  = images_.find(id);
   if(i == images_.end())
   {
      i = images_.insert(i, std::make_pair(id, PdfImage(id)));
   }
   auto &pdf = i->second;
   e.setFilename(filelist_.lookup(e.getNumber()));
   pdf.push_back(e);
}

void ImageContainer::dump()
{
   for(const auto &[id, pdfimage] : images_)
   {
      pdfimage.dump();
   }
}

void ImageContainer::printScript()
{
   for(const auto &[id, pdf]: images_)
   {
      pdf.printScript();
   }
   //   auto images{images_};4
   //   std::cout << "# DEBUG: objs=" << images.size() << std::endl;
   //   //   for(const auto &[id, vec]: images)
   //   std::cout << "# File moves\n";
   //   for(auto i = images.begin(); i != images.end();)
   //   {
   //      if(!hasMaskImage(i->second))
   //      {
   //         for(auto &entry : i->second)
   //         {
   //            auto file   = filelist_.lookup(entry.getNumber());
   //            auto output = std::filesystem::path("output/");
   //            output += file.stem();
   //            output += "_";
   //            output += std::to_string(entry.getObjectId());
   //            output += file.extension();
   //            std::cout << "convert -strip " << file << " " << output << std::endl;
   //            std::cout << "rm " << file << std::endl;
   //         }
   //         i = images.erase(i);
   //      }
   //      else
   //      {
   //         ++i;
   //      }
   //   }
   //
   //   std::cout << "# DEBUG: objs=" << images.size() << std::endl;
   //
   //   std::cout << "# composites";
   //   for(const auto &[id, vec] : images)
   //   {
   //      if(vec.size() % 2 != 0)
   //      {
   //         std::cout << "ID: " << id << std::endl;
   //         throw std::logic_error("WOOOah Boy!");  throw LogicError(__FILE__, __func__, __LINE__) <<
   //      }
   //      for(auto entry = vec.begin(); entry != vec.end();)
   //      {
   //         auto mask = entry + 1;
   //
   //         auto file     = filelist_.lookup(entry->getNumber());
   //         auto maskfile = filelist_.lookup(mask->getNumber());
   //
   //         auto output = std::filesystem::path("output/");
   //         output += file.stem();
   //         output += "_";
   //         output += std::to_string(entry->getObjectId());
   //         output += ".png";
   //
   //         std::cout << "composite -strip -compose CopyOpacity " << maskfile << " " << file << " " << output << std::endl;
   //         std::cout << "rm " << maskfile << " " << file << std::endl;
   //         entry += 2;
   //      }
   //   }
}

bool ImageContainer::hasMaskImage(const std::vector<Entry> &data)
{
   for(const auto &entry : data)
   {
      if(entry.isMask())
      {
         return true;
      }
   }

   return false;
}
