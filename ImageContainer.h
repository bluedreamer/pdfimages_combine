#pragma once
#include <map>
#include <string>
#include <vector>

class Entry;
#include "FileList.h"
#include "PdfImage.h"

class ImageContainer
{
public:
   explicit ImageContainer(std::string prefix, std::string filename);
   void push_back(Entry e);
   void dump();
   void printScript();

private:
   auto hasMaskImage(const std::vector<Entry> &vector) -> bool;

   std::string prefix_;
   FileList    filelist_;
   //   std::map<int, std::vector<Entry>> images_;
   std::map<int, PdfImage> images_;
};
