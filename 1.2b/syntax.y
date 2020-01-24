%{
    #include <stdio.h>
    #include <string.h>
    int yylex();
    void yyerror(); 
    FILE *yyin;
    extern char *yytext;
    extern char *Line;
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
    | TWOP TYPE
    ;
TYPE: INT
    | FLOATT
    | CHART
    | STRINGT
    ;
IDFList:  | IDFS IDF IDFList;
ELSECASE: | ELSE TWOP OPENBRACK INSTRACTION CLOSEBRACK;
INSTRACTION: | IDF INDEX EXPRESSIONI EOI INSTRACTION
    | IF OPENSEP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP TWOP OPENBRACK INSTRACTION CLOSEBRACK ELSECASE END_IF INSTRACTION
    | FOR OPENSEP IDF INDEX TWOP VALUE TWOP EXPRESSION LOGIC_OP EXPRESSION CLOSESEP INSTRACTION END_FOR INSTRACTION
    | SHOW OPENSEP STRING TWOP IDF INDEX CLOSESEP EOI INSTRACTION
    | GET OPENSEP STRING TWOP ADDRESS IDF INDEX CLOSESEP EOI INSTRACTION
    ;
INDEX: | SIZE;
EXPRESSION: IDF INDEX
    | VALUE
    | EXPRESSION ARTH_OP EXPRESSION
    | OPENSEP EXPRESSIONO CLOSESEP
    ;
EXPRESSIONO: VALUE
    | IDF INDEX EXPRESSIONI
    ;
EXPRESSIONI: | AFFECT EXPRESSION
    | ARTH_OP EXPRESSION

VALUE: INTEGER 
    | FLOAT
    | CHAR
    | STRING
    ;

%%

void yyerror(){
    char s[100];
    sprintf(s,"Syntax Error on line %d colom %d : %s", ligne,colom-strlen(yytext),Line);
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