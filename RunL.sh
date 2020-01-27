clear
cd ./MiniAcad/
bison -d ./syntax.y
flex ./project.l
cd ../
gcc ./MiniAcad/lex.yy.c ./MiniAcad/syntax.tab.c -lfl -ly -o App.exe
./App.exe .\input.txt