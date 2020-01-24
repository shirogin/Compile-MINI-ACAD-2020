# <span style="font-family: ROBOTO">Compile Project</span>
## Language Name : <span style="color:rgb(200,30,40);">MINI ACAD </span>

## Table to Save
table | id
----|---
IDF | 0
infix | 1
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

## START AND NEXT TABLE OF THE LANGUAGE GRAMMAR
### ONE

|                 	|                       Debut                      	| Suivant 	|
|:---------------:	|:------------------------------------------------:	|:-------:	|
|       prog      	|                      PROGRAM                     	|         	|
|   DECLARATION   	|                    var, Let, ε                   	|         	|
| TypeDECLARATION 	|                    SIZE, TWOP                    	|         	|
|       TYPE      	|            INT, FLOATT, CHART, STRINGT           	|         	|
|     IDFList     	|                      IDFS, ε                     	|         	|
|     ELSECASE    	|                      ELSE, ε                     	|         	|
|   INSTRACTION   	|            IDF, IF, FOR, SHOW, SHOW, ε           	|         	|
|    CONDITION    	|                  deb(EXPRESSION)                 	|         	|
|      INDEX      	|                      SIZE, ε                     	|         	|
|    EXPRESSION   	| deb(SIGN), deb(EXPRESSION), deb(VALUE), OPENSEP  	|         	|
|   EXPRESSIONO   	|               deb(VALUE), deb(SIGN)              	|         	|
|   EXPRESSIONI   	|             AFFECT , deb(OPERATE), ε             	|         	|
|     OPERATE     	|                   deb(ARTH_OP)                   	|         	|
|      VALUE      	|          INTEGER , FLOAT, CHAR , STRING          	|         	|
|       SIGN      	|                   SUB, ADD , ε                   	|         	|
|     ARTH_OP     	|                SUB, ADD, MUL, DIV                	|         	|

### TWO
