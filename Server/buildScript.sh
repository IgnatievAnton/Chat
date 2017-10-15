#!/bin/bash
cmake ~/Desktop/c++/serverNix/
echo program build
make
i=$(( $(cat version.txt) + 1))
echo $i > version.txt 
echo program create

