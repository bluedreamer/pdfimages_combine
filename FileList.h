#pragma once
#include <filesystem>
#include <map>
#include <string>

#include "ImageFileName.h"

class FileList
{
public:
   FileList(const std::string& dir, const std::string& prefix);
   auto lookup(int number) -> std::optional<ImageFileName>;

private:
   [[nodiscard]] static auto getFileNumber(const std::string &filename) -> int;

   std::map<int, ImageFileName> paths_;
};
