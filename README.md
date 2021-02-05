# pdfimages_combine
Creates a script to combine images and masks extracted from pdf by pdfimages

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

Check the resulting script and run it if you want. NB pdfimages_combine creates a subdirectory called output to put the results in

