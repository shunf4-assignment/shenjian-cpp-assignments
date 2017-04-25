@echo off
set filename=sudoku-inkala
set "filename=%filename%.txt"
set program1=99-b1.exe
rem set program1=1652270-99-b1-0421.exe
set program2=1652340-99-b1-0421.exe
echo/> result.txt
(echo %program1% 
%program1% < %filename% 
echo %program2%
%program2% < %filename%) >> result.txt

(echo %program2%
%program2% < %filename% 
echo %program1% 
%program1% < %filename%) >> result.txt

findstr 本题 result.txt
findstr 计数 result.txt
findstr 秒 result.txt