#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structers
typedef char* type;
char *adapt(char tab[]);
typedef struct Noed{
    type val;
    struct Noed * next;
}Noed;

typedef struct List{
    Noed *Head,
        *Tail;
}List;
typedef union DATA
{
    int *INT;
    float *FLOAT;
    char *CHAR;
    char **STRING;
}DATA;
typedef struct element_t
{
    char *name;
    short type;
    DATA val;
    int size;
    struct element_t *next;
} element;

/* ----------------------------------------------------------------------------------------------------- */
        #define  printType "%s "
/* ----------------------------------------------------------------------------------------------------- */
//List Functions
    void Init(List *list);
    Noed* CreatNoed(type VAL,Noed *next);
    type Pop(List **list);   
    void Push(List **list,type VAL);
    void Pushf(List **list,type VAL);
    type GetVal(List *list);
    int isEmpty(List *list);
    void Print(List *list);
    void PrintL(List *list);
//IDF Functions 
    element* search_IDF(char name[]);
    element* search_CONST(char name[]);
    void push_elem(element **head, char name[]);
    void pushELEM(element **head, char name[],short type);
    void printVALUES(DATA VAL,short type,int size);
    void print_elem(element *head);
    short getType(char name[]);
    void AssignType(element *head,short Type,int Asize);
    void AssignConst(char *name,short Type,char *val);
    element* search_elem(element *head, char name[]);
    void AllocateData(element *head,int size);
    void EVALUE(element *head,char *value,int index);
    void ChangeValueINT(element *head,int val,int Asize);
    void ChangeValueFLOAT(element *head,float val,int Asize);
    void ChangeValueCHAR(element *head,char val,int Asize);
    void ChangeValueSTRING(element *head,char *val,int Asize);

//Lexical Functions
    int nTol(char *s, int *line, int *col);
    void newLine();
    void Insert(char entity[],char* type,short Level);
    void CheckIDF(char entity[]);
    void print_TS();
//Errors Hundeling 
    void SementicError(char *s);
    void LexicalError(char *entity,char *type);
//Sementic Functions
    void show(char *STRING,char *IDF,int index);
    void get(char *STRING,char *IDF,int index);
