#include "FileList.h"
#include "Exceptions.h"

#include <iostream>
#include <regex>

FileList::FileList(const std::string& dir, const std::string& prefix)
{
   for(auto &p : std::filesystem::directory_iterator(dir))
   {
      auto filename = p.path().filename();
      const std::regex filename_regex(prefix + "-[0-9]+-[0-9]+");
      std::string filename_str(filename.string());
      std::smatch sm;
      std::regex_search(filename_str, sm, filename_regex);
//      std::cout << "Filename: " << filename << " Match: " << sm.str() << std::endl;
      if(p.is_regular_file() && !sm.empty())
      {
         // std::cout << "A: " << filename << " B: " << getFileNumber(filename.string()) << std::endl;
         ImageFileName ifn(filename);
         auto          rc = paths_.insert(std::make_pair(getFileNumber(filename_str), filename));

         if(!rc.second)
         {
            throw LogicError(__FILE__, __func__, __LINE__) << "Seems we already have filenum from " + filename_str;
         }
      }
   }
}

auto FileList::getFileNumber(const std::string &filename) -> int
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

auto FileList::lookup(int number) -> std::optional<ImageFileName>
{
   auto rc = paths_.find(number);
   if(rc == paths_.end())
   {
      //            throw LogicError(__FILE__, __func__, __LINE__) << "Cannot find file number:" << number;
      return {};
   }
   return rc->second;
}
