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
    int d=0;
    extern void exit(int status);
    void print_TS();
%}

%token PROGRAM IDF SIZE BEGI END var Let AFFECT EOI ATYPE ADDRESS
%token IDFS OPENSEP TWOP CLOSESEP OPENBRACE CLOSEBRACE OPENBRACK CLOSEBRACK
%token INT FLOATT CHART STRINGT
%token INTEGER FLOAT CHAR STRING
%token GET SHOW IF FOR RETURN ELSE END_IF END_FOR
%token ADD SUB MUL DIV
%token LOGIC_OP

%start prog

%type <mySTRING> STRING PROGRAM IDF SIZE BEGI END var Let AFFECT ATYPE GET SHOW IF FOR RETURN ELSE END_IF END_FOR INT FLOATT CHART STRINGT IDFS OPENSEP TWOP CLOSESEP OPENBRACK CLOSEBRACK OPENBRACE CLOSEBRACE 
%type <myINT> INTEGER
%type <myFLOAT> FLOAT
%type <myCHAR> CHAR ADD SUB MUL DIV EOI ADDRESS 

%union {
    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;
}


%%
prog: PROGRAM IDF DECLARATION BEGI INSTRACTION END{printf("No Syntax Error");};
DECLARATION: | var IDF IDFList TypeDECLARATION EOI DECLARATION
    | Let IDF TWOP INT AFFECT VALUE EOI DECLARATION
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
ELSECASE: | ELSE TWOP OPENBRACE INSTRACTION RETURN OPENSEP EXPRESSIONSP CLOSESEP CLOSEBRACE;
INSTRACTION: | IDFI EXPRESSIONA EOI INSTRACTION
    | IF OPENSEP CONDITION CLOSESEP TWOP IFEXPRESSION ENDIFEXPRESSION INSTRACTION{
        printf("pop END_IF");
        d++;
        //pop END_IFx
        // qudriple()
    }
    | FOR FOREXPRESSION INSTRACTION{
        printf("push FOR");
        d++;
        //push FOR
    }
    | SHOW OPENSEP STRING TWOP SIGN IDF INDEX CLOSESEP EOI INSTRACTION
    | GET OPENSEP STRING TWOP ADDRESS SIGN IDF INDEX CLOSESEP EOI INSTRACTION
    ;
IFEXPRESSION: OPENBRACE INSTRACTION RETURN OPENSEP EXPRESSIONSP CLOSESEP CLOSEBRACE{
    //push '}';
};
ENDIFEXPRESSION: ELSECASE END_IF{
    //push END_IF;
    printf("push END_IF");
};
FOREXPRESSION: OPENSEP SIGN IDF INDEX TWOP VALUE TWOP CONDITION CLOSESEP ENDFOREXPRESSION;
FORINSTRACTION: INSTRACTION{
    // increament IDF
    // jmp FOR
};
ENDFOREXPRESSION: FORINSTRACTION END_FOR{
    //push END_FOR
};
IDFI: IDF INDEX;
EXPRESSIONA: EXPRESSION
    | AFFECT EXPRESSIONSP
    ;
EXPRESSION: | OPER EXPRESSIONSP
    | MSIGN EXPRESSIONSP;
VALIDFI: VALUE
    | IDFI;
OPER: DIV|MUL;
SIGN: | MSIGN;
MSIGN: ADD|SUB;
EXPRESSIONSP: OPENSEP EXPRESSIONSP CLOSESEP EXPRESSION 
    | SIGN VALIDFI EXPRESSIONA;

CONDITION: EXPRESSIONSP LOGIC_OP EXPRESSIONSP;
INDEX: | SIZE
    | OPENBRACK EXPRESSIONSP CLOSEBRACK;
VALUE: INTEGER 
    | FLOAT
    | CHAR
    | STRING
    ;
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