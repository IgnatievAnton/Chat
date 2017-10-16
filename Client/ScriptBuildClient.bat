@echo off
title Script build Client
set /P vers= < ServerVersion.txt
set /a vers+=1
copy nul ServerVersion.txt
ECHO %vers% >>ServerVersion.txt
qmake -o Makefile chatterbox.pro
make
d:
cd qt\5.6\msvc2015_64\bin
windeployqt.exe C:\git\Chat\Client\relese\chatterbox.exe
echo exe file create on path /relese.
c: 
cd C:\git\Chat\Client
git.bat
pause
pause
pause