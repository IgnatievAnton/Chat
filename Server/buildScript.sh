#!/bin/bash
cmake ~/Desktop/c++/serverNix/
echo program build
make
i=$(( $(cat version.txt) + 1))
echo $i > version.txt 
echo program create
cd ..
git add --all
git commit -m "New build Server version $i"
git tag ServerVers$i
git push -u origin master

