#include "../Main.h"
int qumtem = 0;

#include "QUAD.h"
#include "syntaxicf.h"
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
List *IDFLIScT=NULL,
    *EXPRESSIONList=NULL;
short getType(char name[]);
char ELSEetique[100],ENDIFetique[100],FORetique[100],ENDFORetique[100];
int ELSEetiqueI=0,ELSEetiqueC,ENDIFetiqueC,ENDIFetiqueI=0,FORetiqueI=0,ENDFORetiqueI=0,FORetiqueC,ENDFORetiqueC;

//List Quadriple
qdr *ListQdr=NULL;