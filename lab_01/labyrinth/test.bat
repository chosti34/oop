set PROGRAM="%~1"

rem Checking program with non exisiting input file
%PROGRAM% non-existing-input-file.txt %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem Checking program with one console parametr
%PROGRAM% some-non-existing-file.txt
if NOT ERRORLEVEL 1 goto err



echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1