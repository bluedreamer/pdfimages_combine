//
// Created by adrian on 2021-02-04.
//

#include "FileList.h"
#include <iostream>

FileList::FileList(std::string dir, std::string prefix)
{
   for(auto &p : std::filesystem::directory_iterator(dir))
   {
      auto filename = p.path().filename();
      if(p.is_regular_file() && filename.string().find(prefix) == 0)
      {
         // std::cout << "A: " << filename << " B: " << getFileNumber(filename.string()) << std::endl;

         auto rc = paths_.insert(std::make_pair(getFileNumber(filename.string()), filename));

         if(!rc.second)
         {
            throw std::logic_error("Seems we already have filenum from " + filename.string());
         }
      }
   }
}

int FileList::getFileNumber(const std::string &filename) const
{
   auto        i = filename.find('-');
   std::string page;
   ++i;
   while(std::isdigit(filename[i]))
   {
      page += filename[i];
      ++i;
   }
   ++i;
   std::string number;
   while(std::isdigit(filename[i]))
   {
      number += filename[i];
      ++i;
   }
   // std::cout << "X:" << page << " Y:" << number << " ";
   return std::stoi(number);
}

std::filesystem::path FileList::lookup(int number)
{
   auto rc = paths_.find(number);
   if(rc == paths_.end())
   {
      throw std::logic_error("Cannot find file number");
   }
   return rc->second;
}
