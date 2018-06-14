

echo off
set loopcount=50
:loop
PS1_Zad3_Optymalne.exe
set /a loopcount=loopcount-1
if %loopcount%==0 goto exitloop
goto loop
:exitloop
pause


