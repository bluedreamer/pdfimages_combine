# pdfimages_combine
Creates a script to combine images and masks extracted from pdf by pdfimages. Images are copied with stripping to remove metadata to make them deterministic, otherwise there is a timestamp in them when they are extracted from the PDF which is annoying.

# Needed packages
dnf install poppler-utils cmake gcc-c++ 

# Build Instructions
    git submodule init
    mkdir build
    cd build
    cmake -DCMAKE_RELEASE_TYPE=Release ..
    make

# Running it

An example of running it would be

    mkdir images
    cd images
    pdfimages -list ../MyPDF.pdf > list.txt
    pdfimages -p -all ../MyPDF.pdf mypdf
    pdfimages_combine mypdf > script.sh
Optionally get rid of duplicates

    fdupes -N --delete output

Check the resulting script and run it if you want. NB pdfimages_combine creates a subdirectory called output to put the results in

