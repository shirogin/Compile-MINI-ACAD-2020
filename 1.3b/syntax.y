%{
    #include <stdio.h>
    #include <string.h>
    int yylex();
    int yyerror(char* msg); 
    FILE *yyin;
    extern char *yytext;
    extern char *Line;
    extern int colom;
    extern int ligne;
    extern FILE *F;
    extern void exit(int status);
    void print_TS();
%}

%token PROGRAM IDF SIZE BEGI END var Let AFFECT EOI ATYPE ADDRESS
%token IDFS OPENSEP TWOP CLOSESEP OPENBRACK CLOSEBRACK
%token INT FLOATT CHART STRINGT
%token INTEGER FLOAT CHAR STRING
%token GET SHOW IF FOR RETURN ELSE END_IF END_FOR
%token ARTH_OP
%token LOGIC_OP

%start prog

%type <mySTRING> STRING PROGRAM IDF SIZE BEGI END var Let AFFECT ATYPE GET SHOW IF FOR RETURN ELSE END_IF END_FOR INT FLOATT CHART STRINGT IDFS OPENSEP TWOP CLOSESEP OPENBRACK CLOSEBRACK 
%type <myINT> INTEGER
%type <myFLOAT> FLOAT
%type <myCHAR> CHAR ARTH_OP EOI ADDRESS 

%union {
    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;
}


%%
prog: PROGRAM IDF DECLARATION BEGI INSTRACTION END{printf(" no Syntax error");};
DECLARATION: | var IDF IDFList TypeDECLARATION EOI DECLARATION
    | Let IDF TWOP INT AFFECT INTEGER EOI DECLARATION
    ;
TypeDECLARATION: SIZE TWOP ATYPE
    | TWOP TYPE
    ;
TYPE: INT
    | FLOATT
    | CHART
    | STRINGT
    ;
IDFList: | IDFS IDF IDFList;
ELSECASE: | ELSE TWOP OPENBRACK INSTRACTION CLOSEBRACK;
INSTRACTION: | SIGN IDF INDEX EXPRESSIONI EOI INSTRACTION
    | IF OPENSEP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP TWOP OPENBRACK INSTRACTION CLOSEBRACK ELSECASE END_IF INSTRACTION
    | FOR OPENSEP SIGN IDF INDEX TWOP VALUE TWOP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP INSTRACTION END_FOR INSTRACTION
    | SHOW OPENSEP STRING TWOP SIGN IDF INDEX CLOSESEP EOI INSTRACTION
    | GET OPENSEP STRING TWOP ADDRESS SIGN IDF INDEX CLOSESEP EOI INSTRACTION
    ;
INDEX: | SIZE;
EXPRESSION: SIGN IDF INDEX
    | VALUE
    | EXPRESSION OPERATE
    | OPENSEP EXPRESSIONO CLOSESEP
    ;
EXPRESSIONO: VALUE
    | SIGN IDF INDEX EXPRESSIONI
    ;
EXPRESSIONI: | AFFECT EXPRESSION
    | OPERATE
OPERATE: ARTH_OP EXPRESSION
VALUE: INTEGER 
    | FLOAT
    | CHAR
    | STRING
    ;
SIGN: | ARTH_OP{
    if(($1=='/') || ($1 == '*'))
        yyerror("unexpected * or /");
    }
%%

int yyerror(char* msg){
    char s[100];
    sprintf(s,"Syntax Error %s on line %d colom %d : %s",msg, ligne,colom-strlen(yytext),Line);
    printf("\033[1;31m%s\n",s);
    for(int i=0;i<(strlen(s)-strlen(yytext));i++){
        printf(" ");
    }
    printf("^\n\033[0m");
}

int main(int argc, char *argv[]){
    F = fopen(argv[2],"w");
    if( F== NULL)
        {printf("file couldn't be created");
        return (-1);}
    fprintf(F,"1-\t");
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        printf("File doesn't exist");
    else yyparse();
    printf("\n");
    print_TS();
    fclose(F);
    return 0;
}

int yywrap()
{}