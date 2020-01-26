clear
bison -d syntax.y
flex project.l
gcc .\lex.yy.c .\syntax.tab.c -lfl -ly
./a.exe input.txt output.txt