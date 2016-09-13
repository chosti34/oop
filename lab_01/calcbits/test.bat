@echo off

set PROGRAM="calcbits.exe"

rem Program checking...
%PROGRAM% "10"
if ERRORLEVEL 1 goto err



echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1
