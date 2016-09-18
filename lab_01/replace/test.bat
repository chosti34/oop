set PROGRAM="%~1"
                                         
rem Checking file with 'ma' to 'mama'
%PROGRAM% input.txt %TEMP%\output.txt "ma" "mama"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt mama.txt
if ERRORLEVEL 1 goto err

rem Checking file with replace '1231234' to 'x'
%PROGRAM% input.txt %TEMP%\output.txt "1231234" "789"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt 1231234.txt
if ERRORLEVEL 1 goto err

rem Checking file with replace '1' to ''
%PROGRAM% input.txt %TEMP%\output.txt "123" ""
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt empty-output.txt
if ERRORLEVEL 1 goto err

rem Checking program with empty string to search
%PROGRAM% input.txt %TEMP%\output.txt "" "not empty str" > %TEMP%\empty-input.txt
fc.exe %TEMP%\empty-input.txt empty-input.txt 
if ERRORLEVEL 1 goto err

rem Checking with non-existing input file
%PROGRAM% non-existing.txt %TEMP%\output.txt "some str" "another str" > %TEMP%\non-existing.txt
IF NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\non-existing.txt expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

rem Trying to rewrite non-rewritable file (executable program file)
%PROGRAM% input.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err  



echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1