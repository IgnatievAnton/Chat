@echo off
title Script build Client
qmake -o Makefile chatterbox.pro
make
echo exe file create on path /relese.
pause 