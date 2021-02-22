#include "Entry.h"
#include "FileList.h"
#include "ImageContainer.h"
#include <fstream>
#include <iostream>
#include <filesystem>

const char *version="v1.0.2";
auto main(int argc, char *argv[]) -> int
{
   std::filesystem::path binary(argv[0]);
   std::cerr << binary.filename().string() << ' ' << version << std::endl;
   try
   {
      std::string filename = "list.txt";

      if(argc < 2)
      {
         std::cout << "Need to provide at least image prefix you used when extracting\n";
         return 1;
      }
      std::string prefix = argv[1];
      if(argc == 3)
      {
         filename = argv[2];
      }

      std::cerr << "INFO: Reading image list from : " << filename << std::endl;

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
