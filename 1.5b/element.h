#include "OurString.h"

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

void push_elem(element **head, char name[])
{
    element *new_node = (element *)calloc(1,sizeof(element));
    new_node->name = adapt(name);
    new_node->next = *head;
    if (*head == NULL)
        *head = new_node;
    else
        *head=new_node;
}

void print_elem(element *head)
{
    element *current = head;

    while (current != NULL)
    {
        fprintf(F,"Entity: %s  -  ", current->name);
        fprintf(F,"Type: %s", current->type);
        fprintf(F,"  -  Value: %f\n", current->val);
        current = current->next;
    }
}

element* search_elem(element *head, char name[])
{
    element *current = head;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
void SementicError(char *s);
void AllocateData(element *head);
void AssignType(element *head,short Type,int Asize){
    if(head!=NULL){
        head->type=Type;
        head->size=Asize;
        AllocateData(head);
    }else
        SementicError("Variable couldn't be declared");
}
void AssignConst(){

}
void AllocateData(element *head){
    switch (head->type)
    {
    case 0:
        head->val.INT=(int*)calloc(head->size,sizeof(int));
        break;
    case 1:
        head->val.FLOAT=(float*)calloc(head->size,sizeof(float));
        break;
    case 2:
        head->val.CHAR=(char*)calloc(head->size,sizeof(char));
        break;
    case 3:
        head->val.STRING=(char**)calloc(head->size,sizeof(char*));
        break;
    default:
        printf("error type");
        break;
    }
}
void ChangeValueINT(element *head,int val,int Asize){
    if((head!=NULL) && (head->size!=0) && (head->type==0) ){
        *(head->val.INT+Asize)=val;
    }else
        SementicError("Variable couldn't be Changed");
}
void ChangeValueFLOAT(element *head,float val,int Asize){
    if((head!=NULL) && (head->size!=0) && (head->type==1)){
        *(head->val.FLOAT+Asize)=val;
    }else
        SementicError("Variable couldn't be declared");
}
void ChangeValueCHAR(element *head,char val,int Asize){
    if((head!=NULL) && (head->size!=0) && (head->type==2)){
        *(head->val.CHAR+Asize)=val;
    }else
        SementicError("Variable couldn't be declared");
}
void ChangeValueSTRING(element *head,char *val,int Asize){
    if((head!=NULL) && (head->size!=0) && (head->type==3)){
        *(head->val.STRING+Asize)=val;
    }else
        SementicError("Variable couldn't be declared");
}

