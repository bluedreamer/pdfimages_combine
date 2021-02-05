#pragma once
#include <filesystem>
#include <map>
#include <string>

#include "ImageFileName.h"

class FileList
{
public:
   FileList(std::string dir, std::string prefix);
   auto lookup(int number) -> std::optional<ImageFileName>;

private:
   [[nodiscard]] auto getFileNumber(const std::string &filename) const -> int;

   std::map<int, ImageFileName> paths_;
};
