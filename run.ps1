clear
cd ./MiniAcad/
bison -d ./syntax.y
flex ./project.l
cd ../
gcc ./MiniAcad/lex.yy.c ./MiniAcad/syntax.tab.c -lfl -ly -o App.exe
Remove-Item ./MiniAcad/lex.yy.c -r -fo 
Remove-Item ./MiniAcad/syntax.tab.c -r -fo 
Remove-Item ./MiniAcad/syntax.tab.h -r -fo 
./App.exe .\input.txt