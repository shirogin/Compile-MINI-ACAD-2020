#include "StringList.h"
int colom = 1, 
    ligne = 1,
    Decalaration = 1;
char *Line;


// Returns new Line
void newLine()
{
    ligne++;
    colom = 1;
    fprintf(F,"\n%d-\t", ligne);
    free(Line);
    Line=NULL;
}
// Declare variables
element *listIDF = NULL;/* IDF and CONST*/
List *listInfix = NULL, /* infix */
    *listComments = NULL /* COMMENTS*/;
void print_TS();
void SementicError(char *s){
    printf("\033[1;33mSementic Error in line %d  colom %d : %s \n\033[0m",ligne,colom-strlen(yytext),s);
    print_TS();
    exit(-1);
}
void Insert(char entity[],char* type,short Level){
    if(Line==NULL){
        Line=(char*)malloc(1000*sizeof(char));
        strcpy(Line,entity);
    }else
        strcat(Line,entity);
    colom = colom + strlen(entity);
    fprintf(F,"| %s : %s ", type, entity);
    Pushf(&listInfix,entity, Level);
}
void CheckIDF(char entity[]){
    char d[100];
    if(Decalaration){
        if (search_elem(listIDF, entity)==NULL){
            push_elem(&listIDF,entity);
            return;
        }
        sprintf(d,"var '%s' is already declared",entity);
    }
    else if(search_elem(listIDF, entity)!=NULL)
        return;
    else
        sprintf(d,"this var '%s' isn't declared before",entity);
    SementicError(d);
}

void LexicalError(char *entity,char *type){
    if(Line==NULL){
        Line=(char*)malloc(1000*sizeof(char));
        strcpy(Line,entity);
    }else
        strcat(Line,entity);
    printf("\033[1;35mLexical Error %s : %s \n\033[0m", type, entity);
    fprintf(F,"|    Lexical Error %s : %s \n", type, entity);
}
void Comment(char *entity){
    fprintf(F,"| A Comment : ");
    nTol(entity, &ligne, &colom);
    Pushf(&listComments,entity, 0);
}

void print_TS()
{
    fprintf(F,"\n------------------ IDF Table ------------------\n");
    print_elem(listIDF);

    fprintf(F,"\n------------------ Comments Table ------------------\n");
    Print(listComments);

    fprintf(F,"\n------------------ Infixe Table ------------------\n");
    Print(listInfix);
}