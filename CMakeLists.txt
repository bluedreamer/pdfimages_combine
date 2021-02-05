# cmake_minimum_required(VERSION <specify CMake version here>)
project(pdfimages_combine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(pdfimages_combine main.cpp Entry.cpp Entry.h ImageContainer.cpp ImageContainer.h FileList.cpp FileList.h)
