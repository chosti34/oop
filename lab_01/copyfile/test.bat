@echo off

set PROGRAM="copyfile.exe"

rem �������� � ������ ������
%PROGRAM% empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt empty.txt
if ERRORLEVEL 1 goto err

rem �������� � ������������ ������
%PROGRAM% one-line.txt %TEMP%\one-line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\one-line.txt one-line.txt
if ERRORLEVEL 1 goto err

rem �������� � ������������� ������
%PROGRAM% multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multiline.txt multiline.txt
if ERRORLEVEL 1 goto err




echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1