#pragma once
#include <map>
#include <string>
#include <vector>

class Entry;
#include "FileList.h"

class ImageContainer
{
public:
   explicit ImageContainer(std::string prefix);
   void push_back(Entry e);
   void dump();
   void printScript();

private:
   bool hasMaskImage(const std::vector<Entry> &vector);

   std::string                       prefix_;
   FileList                          filelist_;
   std::map<int, std::vector<Entry>> images_;
};
