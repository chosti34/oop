set PROGRAM="%~1"

rem Checking with non-existing file...
%PROGRAM% non-existing-file.txt
if NOT ERRORLEVEL 1 goto err

rem Checking with determinant equals to zero
%PROGRAM% zero-determinant-matrix.txt
if NOT ERRORLEVEL 1 goto err

rem Checking with identity matrix
%PROGRAM% identity-matrix.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt identity-matrix.txt
if ERRORLEVEL 1 goto err

rem Checking with some matrix
%PROGRAM% some-matrix.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt some-matrix-inversed.txt
if ERRORLEVEL 1 goto err 

echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1
