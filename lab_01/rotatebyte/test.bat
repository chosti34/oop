set PROGRAM="%~1"

rem Checking max value of byte
%PROGRAM% 255 9 R > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt max-byte.txt
if ERRORLEVEL 1 goto err

rem Checking with too high value of byte
%PROGRAM% 300 2 L
if NOT ERRORLEVEL 1 goto err

rem Checking some random values (2 2 R) => maxbyte
%PROGRAM% 2 2 R > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt two-power-seven.txt
if ERRORLEVEL 1 goto err



echo Program testing succedeed!
exit 0

:err
echo Program testing failed...
exit 1
