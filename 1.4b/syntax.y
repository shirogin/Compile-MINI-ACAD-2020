%{
    #include "SYM.h"
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
    List *IDFLIScT=NULL;
    short getType(char name[]);
    char ELSEetique[100],ENDIFetique[100],FORetique[100],ENDFORetique[100];
    int ELSEetiqueI=0,ELSEetiqueC,ENDIFetiqueC,ENDIFetiqueI=0,FORetiqueI=0,ENDFORetiqueI=0,FORetiqueC,ENDFORetiqueC;
%}

%token PROGRAM IDF SIZE BEGI END var Let AFFECT EOI ADDRESS
%token IDFS OPENSEP TWOP CLOSESEP OPENBRACE CLOSEBRACE OPENBRACK CLOSEBRACK
%token <myINT> ITYPE FTYPE STYPE CTYPE
%token INTEGER FLOAT CHAR STRING
%token GET SHOW IF FOR RETURN ELSE END_IF END_FOR
%token ADD SUB MUL DIV
%token LOGIC_OP

%start prog

%type <mySTRING> STRING PROGRAM IDF BEGI END var Let AFFECT GET SHOW IF FOR RETURN ELSE END_IF END_FOR IDFS OPENSEP TWOP CLOSESEP OPENBRACK CLOSEBRACK OPENBRACE CLOSEBRACE VALUE FLOAT INTEGER CHAR
%type <myINT> SIZE TYPE INDEX
%type <myCHAR> ADD SUB MUL DIV EOI ADDRESS 

%union {
    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;
}


%%
prog: PROGRAM IDF DECLARATION BEGI INSTRACTION END{
    AssignConst($2, 0, "0\0");
    printf("\nNo Syntax Error");
};
DECLARATION: | var FIRSTVAR TypeDECLARATION EOI DECLARATION
    | CONSTDECLARATION DECLARATION
    ;
CONSTDECLARATION: Let IDF TWOP TYPE AFFECT VALUE EOI{
    switch($4){
        case 0: 
            if($4!=getType($6)){
                SementicError("Error: TYPE conflict, expected INT");
            }else{
                AssignConst($2, $4, $6);
            }
            printf("CONST %s=%s INT\n",$2,$6);
            break;
        case 1:
            if($4!=getType($6)){
                SementicError("Error: TYPE conflict, expected FLOAT");
            }else{
                AssignConst($2, $4, $6);
                
            }
            printf("CONST %s=%s FLOAT\n",$2,$6);
            break;
        case 2:
            if($4!=getType($6)){
                SementicError("Error: TYPE conflict, expected CHAR");
            }else{
                AssignConst($2, $4, $6);
            }
            printf("CONST %s=%s CHAR\n",$2,$6);
            break;
        case 3:
            if($4!=getType($6)){
                SementicError("Error: TYPE conflict, expected STRING");
            }else{
                AssignConst($2, $4, $6);
            }
            printf("CONST %s=%s STRING\n",$2,$6);
            break;
    }
};
FIRSTVAR: IDF IDFList{
    printf(" %s ",$1);
    Push(&IDFLIScT,$1,0);
};
TypeDECLARATION: SIZE TWOP TYPE{
    printf("array type is %d[%d]\n",$3,$1);
    // pop all idf and made them of this type with this size $1
    while(isEmpty(*IDFLIScT)==0){
        element *current=search_IDF(Pop(IDFLIScT));
        if(current!=NULL)
            AssignType(current,$3,$1);
    }
}
    | TWOP TYPE{
        printf("type is %d\n",$2);
        while(isEmpty(*IDFLIScT)==0){
        element *current=search_IDF(Pop(IDFLIScT));
        if(current!=NULL)
            AssignType(current,$2,1);
        }
    // pop all idf and made them of this type
    }
    ;
TYPE: ITYPE | FTYPE | STYPE | CTYPE;
IDFList: | IDFS IDF IDFList{
    printf(" %s ",$2);
    //push to idf list
    Push(&IDFLIScT,$2,0);

};
ELSECASE: | ELSE TWOP OPENBRACE INSTRACTION RETURN OPENSEP EXPRESSIONSP CLOSESEP CLOSEBRACE;
INSTRACTION: | IDFI EXPRESSIONA EOI INSTRACTION
    | IFINSTRACTION INSTRACTION
    | FORINSTRACTION INSTRACTION
    | SHOWINSTRACTION INSTRACTION
    | GETINSTRACTION INSTRACTION
    ;
GETINSTRACTION: GET OPENSEP STRING TWOP ADDRESS IDF INDEX CLOSESEP EOI{
    get($3,$6,$7);
};
SHOWINSTRACTION: SHOW OPENSEP STRING TWOP IDF INDEX CLOSESEP EOI{
    show($3,$5,$6);
};
FORINSTRACTION: FORETI FOREXPRESSION END_FOR {
    //change END for etique
    sprintf(ENDFORetique,"etique %d",ENDFORetiqueC);
    printf("change EnD for %s\n",ENDFORetique);
};
FORETI: FOR{
    sprintf(FORetique,"etique %d",FORetiqueI);
    printf("create For ETIQUE\n");
    FORetiqueC=FORetiqueI;
    FORetiqueI++;

}
IFINSTRACTION: IF IFCONDITION TWOP IFEXPRESSION ENDIFEXPRESSION{
        //pop END_IFx
    };
IFCONDITION:OPENSEP CONDITION CLOSESEP{
    sprintf(ELSEetique,"etique %d",ELSEetiqueI);
    printf("condition then if with %s\n",ELSEetique);
    ELSEetiqueI++;
    ELSEetiqueC=ELSEetiqueI;
    
};
IFEXPRESSION: OPENBRACE INSTRACTION RETURNEXPRESSION CLOSEBRACE{
    ELSEetiqueC--;
    sprintf(ELSEetique,"etique %d",ELSEetiqueC);
    printf("changing %s of }\n",ELSEetique);

};
RETURNEXPRESSION: RETURN OPENSEP EXPRESSIONSP CLOSESEP{
    sprintf(ENDIFetique,"etique %d",ENDIFetiqueI);
    printf("QUAD EXPRESSION RETURN %s %d\n",ENDIFetique,ligne);
    ENDIFetiqueI++;
    ENDIFetiqueC=ENDIFetiqueI;
};
ENDIFEXPRESSION: ELSECASE END_IF{
    //push END_IF;
    ENDIFetiqueC--;
    sprintf(ENDIFetique,"etique %d",ENDIFetiqueC);
    printf("changing %s of END iF\n",ENDIFetique);
};
FOREXPRESSION: OPENSEP SIGN IDF INDEX TWOP VALUE TWOP FORCONDITION CLOSESEP ENDFOREXPRESSION{
    
};
FORCONDITION: CONDITION{
    //do condition evaluation
    sprintf(ENDIFetique,"etique %d",ENDIFetiqueI);
    printf("create END FOR %s and do condition\n",ENDIFetique);
};
ENDFOREXPRESSION: INSTRACTION{
    // increament IDF
    // jmp FOR
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
INDEX: {$$=0;}| SIZE{
    //$$=size
    $$=$1;
}
    | OPENBRACK IDF CLOSEBRACK{
        //check idf if its int;
    };
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