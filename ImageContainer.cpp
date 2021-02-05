#include "ImageContainer.h"
#include "Entry.h"
#include "FileList.h"
#include <iostream>
#include <stdexcept>
#include <string>

ImageContainer::ImageContainer(std::string prefix)
   : prefix_(prefix)
   , filelist_(".", prefix)
{
}

void ImageContainer::push_back(Entry e)
{
   images_[e.getObjectId()].push_back(e);
}

void ImageContainer::dump()
{
   for(const auto &[id, vec] : images_)
   {
      std::cout << id << " has " << vec.size() << std::endl;
      // if(vec.size()!=1 && vec.size() % 2 != 0)
      // {
      //     throw std::logic_error("WOOOah Boy!");
      // }
   }
}

void ImageContainer::printScript()
{
   auto images{images_};
   std::cout << "# DEBUG: objs=" << images.size() << std::endl;
   //   for(const auto &[id, vec]: images)
   std::cout << "# File moves\n";
   for(auto i = images.begin(); i != images.end();)
   {
      if(!hasMaskImage(i->second))
      {
         for(auto &entry : i->second)
         {
            auto file   = filelist_.lookup(entry.getNumber());
            auto output = std::filesystem::path("output/");
            output += file.stem();
            output += "_";
            output += std::to_string(entry.getObjectId());
            output += file.extension();
            std::cout << "convert -strip " << file << " " << output << std::endl;
            std::cout << "rm " << file << std::endl;
         }
         i = images.erase(i);
      }
      else
      {
         ++i;
      }
   }

   std::cout << "# DEBUG: objs=" << images.size() << std::endl;

   std::cout << "# composites";
   for(const auto &[id, vec] : images)
   {
      if(vec.size() % 2 != 0)
      {
         std::cout << "ID: " << id << std::endl;
         throw std::logic_error("WOOOah Boy!");
      }
      for(auto entry = vec.begin(); entry != vec.end();)
      {
         auto mask = entry + 1;

         auto file     = filelist_.lookup(entry->getNumber());
         auto maskfile = filelist_.lookup(mask->getNumber());

         auto output = std::filesystem::path("output/");
         output += file.stem();
         output += "_";
         output += std::to_string(entry->getObjectId());
         output += ".png";

         std::cout << "composite -strip -compose CopyOpacity " << maskfile << " " << file << " " << output << std::endl;
         std::cout << "rm " << maskfile << " " << file << std::endl;
         entry += 2;
      }
   }
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
