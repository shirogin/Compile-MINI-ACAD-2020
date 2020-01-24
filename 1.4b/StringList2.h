#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char* type;
typedef struct Noed{
    type val;
    int Level;
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
void AssignType(element *head,short Type,int Asize);
void AssignConst(char *name,short Type,char *val);
type Pop(List *list);
void Push(List **list,type VAL,int Level);
element* search_elem(element *head, char name[]);
element* search_IDF(char name[]);
int isEmpty(List list);
void SementicError(char *s);

