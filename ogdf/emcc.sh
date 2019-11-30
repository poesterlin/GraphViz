#!/bin/sh

# exit on error
set -e

path="."

if [ -z "$1" ]
  then
    echo "No filename supplied. Run: sh compile.sh [--skip (optional, to skip the ogdf build)] file1 file2 ..."
    exit 1
  else
    if [ $1 = "--skip" ]
      then
          echo --- skip ogdf build
          shift
      else
        echo --- cmake
        cmake -DOGDF_WARNING_ERRORS=OFF $path

        echo --- make
        make -j16
      fi
fi

echo --- compile source files
FILES=""
while [ $# -gt 0 ]     
do                   
    em++ -std=c++11 -O0 -I$path/include -I$path/src -o $1.bc -c $1
    FILES="${FILES} $1.bc"
    shift                  
done

echo --- link source files
em++ -std=c++11 -s WASM=1 -O0 -o hello.html -L$path/ $FILES -lOGDF -lCOIN --memory-init-file 0

echo --- change access rights
chmod +x output_binary.bin

echo --- run binary
echo "\n\r\n\r\n\r\n\r"
./output_binary.bin
