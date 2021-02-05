#include "ImageContainer.h"
#include "Entry.h"
#include "FileList.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

ImageContainer::ImageContainer(const std::string& prefix, const std::string& filename)
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

      Entry entry(std::move(line));
      push_back(std::move(entry));
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
   pdf.push_back(std::move(e));
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
   for(const auto &[id, pdf] : images_)
   {
      pdf.printScript();
   }
}
