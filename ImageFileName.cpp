#include "ImageFileName.h"

ImageFileName::ImageFileName(std::filesystem::path filename)
   : filename_(filename)
{
   auto        filename_str = filename.string();
   auto        i            = filename_str.find('-');
   std::string page_str;
   ++i;
   while(std::isdigit(filename_str[i]))
   {
      page_str += filename_str[i];
      ++i;
   }
   ++i;
   std::string number_str;
   while(std::isdigit(filename_str[i]))
   {
      number_str += filename_str[i];
      ++i;
   }
   // std::cout << "X:" << page << " Y:" << number << " ";

   page_number_  = std::stoi(page_str);
   image_number_ = std::stoi(number_str);
}
