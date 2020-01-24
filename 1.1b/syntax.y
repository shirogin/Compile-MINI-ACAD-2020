%{
    #include <stdio.h>
    #include <string.h>
    int yylex();
    int yyerror(char *msg); 
    FILE *yyin;
    extern char *yytext;
    extern int colom;
    extern int ligne;
    extern FILE *F;
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


%%
prog: PROGRAM IDF DECLARATION BEGI INSTRACTION END{printf(" no Syntax error");};
DECLARATION: | var IDF IDFList TypeDECLARATION EOI DECLARATION
    | Let IDF TWOP INT AFFECT INTEGER EOI DECLARATION
    ;
TypeDECLARATION: SIZE TWOP ATYPE
    | TWOP TYPE;
TYPE: INT
    | FLOATT
    | CHART
    | STRINGT
    ;
IDFList:  | IDFS IDF IDFList;
ELSECASE: | ELSE TWOP OPENBRACK INSTRACTION CLOSEBRACK;
INSTRACTION: | IDF EXPRESSIONI EOI INSTRACTION
    | IF OPENSEP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP TWOP OPENBRACK INSTRACTION CLOSEBRACK ELSECASE END_IF INSTRACTION
    | FOR OPENSEP IDF TWOP VALUE TWOP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP INSTRACTION END_FOR INSTRACTION
    | SHOW OPENSEP STRING TWOP IDF CLOSESEP EOI INSTRACTION
    | GET OPENSEP STRING TWOP ADDRESS IDF CLOSESEP EOI INSTRACTION
    ;
EXPRESSION: IDF 
    | VALUE
    | EXPRESSION ARTH_OP EXPRESSION
    | OPENSEP EXPRESSIONO CLOSESEP
    ;
EXPRESSIONO: VALUE
    | IDF EXPRESSIONI
    ;
EXPRESSIONI: | AFFECT EXPRESSION
    | ARTH_OP EXPRESSION

VALUE: INTEGER 
    | FLOAT
    | CHAR
    | STRING
    ;

%%

int yyerror(char *s){
    printf("Syntax Error on line %d colom %d : %s\n", ligne,colom-strlen(yytext),yytext);
    return 0;
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
    return 0;
}

int yywrap()
{}