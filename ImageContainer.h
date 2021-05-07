#pragma once
#include <map>
#include <string>
#include <vector>

class Entry;
#include "FileList.h"
#include "PdfImage.h"

/**
 * @class Manages the process of combining images from the PDF
 */
class ImageContainer
{
public:
   /**
    * Create a new ImageContainer. Parses all the information for files in directory and list.txt
    *
    * @param prefix The prefix given when extracting the images with pdfimages
    * @param filename Filename containing the output of 'pdfimages -list' usually list.txt
    */
   ImageContainer(const std::string& prefix, const std::string& filename);


   /**
    *
    */
   void dump();

   /**
    * Bash script to run the necessary imagick commands to get the recombined images
    */
   void printScript();

private:
   void push_back(Entry entry);

   std::string prefix_;
   FileList    filelist_;
   std::map<ImageReference, PdfImage> image_map_;
};
