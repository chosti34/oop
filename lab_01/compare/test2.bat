@echo off

set PROGRAM="compare.exe"

rem Equal files checking...
%PROGRAM% "file1.txt" "file2.txt"
if ERRORLEVEL 1 goto err

rem Non-equal files checking...
%PROGRAM% "file1.txt" "file3.txt"
if ERRORLEVEL 1 goto ok

:ok
echo Program testing succedeed!
exit 0

:err
echo Program testing failed...
exit 1