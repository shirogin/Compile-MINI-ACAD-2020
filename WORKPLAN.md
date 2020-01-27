# <span style="font-family: ROBOTO">Compile Project</span>
## Language Name : <span style="color:rgb(200,30,40);">MINI ACAD </span>

## Table to Save
table | id
----|---
IDF | 0
Values | 1
Comments | 2

### **<span style="color:purple;">DECLARATION Types</span>**
Types	|   ID
:------:|:------:
INT |	0
FLOAT | 1
CHAR |  2 
STRING |    3

### **<span style="color:purple;">CONST/VAR/ARRAY</span>**

Types	|   size
:------:|:------:
CONST |	0
VARIABLE | 1
ARRAY |  1 < size 

## Variable Declaration in the program
    if declaration
        if exist
            error("var is already declared")
        else 
            create()
    else if(!exist)
        error("this var isn't declared")

### Files Created 

Files Name	|   size
:----------:|:------:
App.exe |	the program to compile the Input.txt
Lexical.txt | lexical treatment + TS
Quadriples.txt |  Quadriples list 
DeclarationF.txt |  Var Declaration
### Run your program 
> lunch this command for windows : ./run.ps1

> lunch this command for Linux : ./run.ps1

