#!/bin/sh

# exit on error
set -e

path="./lib"

echo --- cmake
cmake -DOGDF_WARNING_ERRORS=OFF $path

echo --- make
make -j16


echo --- compile source files
FILES=""
while [ $# -gt 0 ]     
do                   
    g++ -std=c++11 -I$path/include -I$path/src -o $1.o -c $1.cpp
    FILES="${FILES} $1.o"
    shift                  
done

echo --- link source files
g++ -std=c++11 -o output_binary.bin -L$path/ $FILES -lOGDF -lCOIN

echo --- delete o files
rm $FILES

echo --- change access rights
chmod +x output_binary.bin

echo --- run binary
./output_binary.bin
