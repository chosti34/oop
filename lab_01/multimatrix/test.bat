set PROGRAM="%~1"

rem Checking with non-existing input files...
%PROGRAM% input1.txt input2.txt
if NOT ERRORLEVEL 1 goto err

rem Checking with identity matrix
%PROGRAM% identity-matrix.txt some-matrix.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt some-matrix.txt
if ERRORLEVEL 1 goto err



echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1