@echo off

set PROGRAM="replace.exe"

rem Checking file with 're' to 'rere'
%PROGRAM% input.txt output.txt "re" "rere"
if ERRORLEVEL 1 goto err
fc.exe output.txt rere-correct.txt
if ERRORLEVEL 1 goto err

rem Checking file with replace '1231234' to 'x'
%PROGRAM% input.txt output.txt "1231234" "x"
if ERRORLEVEL 1 goto err
fc.exe output.txt 1231234-correct.txt
if ERRORLEVEL 1 goto err

rem Checking file with replace '1' to ''
%PROGRAM% input.txt output.txt "1" ""
if ERRORLEVEL 1 goto err
fc.exe output.txt empty-str-correct.txt
if ERRORLEVEL 1 goto err



echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1