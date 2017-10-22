@echo off
title Script build Client
set /P vers= < ServerVersion.txt
set /a vers+=1
copy nul ServerVersion.txt
ECHO %vers% >>ServerVersion.txt
qmake -o Makefile chatterbox.pro
make
echo exe file create on path /relese.
d:
cd qt\5.6\msvc2015_64\bin
windeployqt.exe C:\git\Chat\Client\release\chatterbox.exe
c:
cd C:\git\Chat\Client\relese
DEL /F /S /Q /A qrc_qmake_qmake_immediate.cpp
cd C:\git\Chat\Client
compil32 /cc setuppcreatescript.iss
git.bat