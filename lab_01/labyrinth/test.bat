set PROGRAM="%~1"

rem Checking program with non exisiting input file
%PROGRAM% non-existing-input-file.txt %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem Checking program with one console parametr
%PROGRAM% some-non-existing-file.txt
if NOT ERRORLEVEL 1 goto err

rem Testing program with no start and finish point
%PROGRAM% no-start-and-finish-point.txt %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem Testing program with some random labyrinth
%PROGRAM% map1.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt path1.txt
if ERRORLEVEL 1 goto err

rem Testing program with some another map
%PROGRAM% map2.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt path2.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1