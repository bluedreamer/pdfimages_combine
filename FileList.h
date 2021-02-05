#pragma once
#include <filesystem>
#include <map>
#include <string>

class FileList
{
public:
   FileList(std::string dir, std::string prefix);
   std::filesystem::path lookup(int number);

private:
   int getFileNumber(const std::string &filename) const;

   std::map<int, std::filesystem::path> paths_;
};
