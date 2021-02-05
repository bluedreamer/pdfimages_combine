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

      ImageContainer images(prefix, filename);
      //      images.dump();
      images.printScript();
   }
   catch(const std::exception &e)
   {
      std::cerr << "EXCEPTION: " << e.what() << std::endl;
   }

   return 0;
}
