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
   ImageContainer(const std::string& prefix, const std::string& filename);
   void push_back(Entry e);
   void dump();
   void printScript();

private:
   std::string prefix_;
   FileList    filelist_;
   std::map<int, PdfImage> images_;
};
