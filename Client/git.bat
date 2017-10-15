@echo off
set /P vers= < ServerVersion.txt
cd ..
git add .
git commit -m "New build clientProject version %vers%"
git tag Client %vers%
git push -u origin master