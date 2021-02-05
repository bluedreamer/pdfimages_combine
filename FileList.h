#pragma once
#include <filesystem>
#include <map>
#include <string>

#include "ImageFileName.h"

class FileList
{
public:
   FileList(std::string dir, std::string prefix);
   std::optional<ImageFileName> lookup(int number);

private:
   int getFileNumber(const std::string &filename) const;

   std::map<int, ImageFileName> paths_;
};
