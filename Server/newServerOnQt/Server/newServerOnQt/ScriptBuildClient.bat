@echo off
qmake -o Makefile OfficeChatServer.pro
make
echo exe file create on path /relese.
d:
cd qt\5.6\msvc2015_64\bin
windeployqt.exe C:\git\Chat\Server\newServerOnQt\release\ChattYServer.exe
