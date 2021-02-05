cmake_minimum_required(VERSION 3.16)
project(pdfimages_combine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(pdfimages_combine main.cpp Entry.cpp Entry.h ImageContainer.cpp ImageContainer.h FileList.cpp FileList.h PdfImage.cpp PdfImage.h ImageFileName.cpp ImageFileName.h Exceptions.h)
