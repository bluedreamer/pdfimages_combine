#include "Entry.h"
#include "FileList.h"
#include "ImageContainer.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
   try
   {
      std::string filename = "list.txt";

      if(argc < 2)
      {
         std::cout << "Need to provide at least image prefix\n";
         return 1;
      }
      std::string prefix = argv[1];
      if(argc == 3)
      {
         filename = argv[2];
      }

      std::ifstream in(filename.c_str());
      int           lineno = 0;
      std::string   line;

      ImageContainer images(prefix);
      while(std::getline(in, line))
      {
         // std::cout << line << std::endl;
         ++lineno;
         if(lineno < 3)
         {
            continue;
         }

         Entry entry(line);
         images.push_back(entry);
      }

      // images.dump();
      images.printScript();
   }
   catch(const std::exception &e)
   {
      std::cout << "EXCEPTION: " << e.what() << std::endl;
   }

   return 0;
}
