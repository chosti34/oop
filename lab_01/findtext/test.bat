@echo off

set PROGRAM="findtext.exe"

rem Existing substr checking...
%PROGRAM% "not-empty.txt" "other"
if ERRORLEVEL 1 goto err

rem Non-existing substr checking...
%PROGRAM% "not-empty.txt" "some-str"
if ERRORLEVEL 0 goto success



:success
echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1 