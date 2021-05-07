#include "ImageContainer.h"
#include "Entry.h"
#include "FileList.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

ImageContainer::ImageContainer(const std::string &prefix, const std::string &filename)
   : prefix_(prefix)
   , filelist_(".", prefix)
{
   std::ifstream in(filename.c_str());
   int           lineno = 0;
   std::string   line;

   /**
    * Process list.txt file and parse into Entry's
    */
   while(std::getline(in, line))
   {
      // std::cout << line << std::endl;
      ++lineno;
      if(lineno < 3)
      {
         // Skip column headings
         continue;
      }

      Entry entry(std::move(line));
      auto image_filename = filelist_.lookup(entry.getNumber());
      entry.setFilename(image_filename);
      push_back(std::move(entry));
   }

   if(image_map_.empty())
   {
      throw LogicError(__FILE__, __func__, __LINE__) << "No entries read from pdfimages -list output file: " << filename;
   }
}

void ImageContainer::push_back(Entry entry)
{
   const auto &img_ref = entry.getImageReference();
   auto        iterator = image_map_.find(img_ref);
   if(iterator == image_map_.end())
   {
      iterator = image_map_.insert(iterator, std::make_pair(img_ref, PdfImage(img_ref)));
   }
   auto &pdf_image = iterator->second;
   pdf_image.push_back(std::move(entry));
}

void ImageContainer::dump()
{
   for(const auto &[id, pdfimage] : image_map_)
   {
      pdfimage.dump();
   }
}

void ImageContainer::printScript()
{
   for(const auto &[id, pdf] : image_map_)
   {
      pdf.printScript();
   }
}
