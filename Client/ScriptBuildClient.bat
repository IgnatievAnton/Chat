@echo off
title Script build Client
set /P vers= < ServerVersion.txt
set /a vers+=1
copy nul ServerVersion.txt
ECHO %vers% >>ServerVersion.txt
qmake -o Makefile chatterbox.pro
make
echo exe file create on path /relese.
git.bat