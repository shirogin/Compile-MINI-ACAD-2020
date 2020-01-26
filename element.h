#include "OurString.h"
#include "StringList2.h"


void AssignType(element *head,short Type,int Asize);

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
void pushELEM(element **head, char name[],short type){
    push_elem(head,name);
    (*head)->type=type;
}
void printVALUES(DATA VAL,short type,int size){
    if(size==0){
        switch (type)
        {
        case 0:
            fprintf(F,"%d",VAL.INT[0]);
            break;
        case 1:
            fprintf(F,"%f",VAL.FLOAT[0]);
            break;
        case 2:
            fprintf(F,"%c",VAL.CHAR[0]);
            break;
        case 3:
            fprintf(F,"%s",VAL.STRING[0]);
            break;
        }
        fprintf(F," CONST\n");
    }else{
        fprintf(F,"[ ");
        switch (type)
        {
        case 0:
            for(int i=0;i<size-1;i++){
                fprintf(F,"%d , ",VAL.INT[i]);
            } 
            fprintf(F,"%d ]\n",VAL.INT[size-1]);
            break;
        case 1:
            for(int i=0;i<size-1;i++){
                fprintf(F,"%f , ",VAL.FLOAT[i]);
            } 
            fprintf(F,"%f ]\n",VAL.FLOAT[size-1]);
            break;
        case 2:
            for(int i=0;i<size-1;i++){
                fprintf(F,"%c , ",VAL.CHAR[i]);
            } 
            fprintf(F,"%c ]\n",VAL.CHAR[size-1]);
            break;
        case 3:
            for(int i=0;i<size-1;i++){
                fprintf(F,"%s , ",VAL.STRING[i]);
            } 
            fprintf(F,"%s ]\n",VAL.STRING[size-1]);
            break;
        }
                
    }
    
}
void print_elem(element *head)
{
    element *current = head;
    char *type,value[100];
    while (current != NULL)
    {
        fprintf(F,"Entity: %s  -  ", current->name);
        switch (current->type)
        {
            case 0:
                type = adapt("INT");
                break;
            case 1:
                type = adapt("FLOAT");
                break;
            case 2:
                type = adapt("CHAR");
                break;
            case 3:
                type =adapt("STRING");
                break;
        }
        fprintf(F,"Type: %s", type);
        fprintf(F,"  -  Value: ");
        printVALUES(current->val,current->type,current->size);
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
void AllocateData(element *head,int size);
void AssignType(element *head,short Type,int Asize){
    if(head!=NULL){
        head->type=Type;
        head->size=Asize;
        AllocateData(head,Asize);
    }else
        SementicError("Variable couldn't be declared");
}
void AllocateData(element *head,int size){
    switch (head->type)
    {
    case 0:
        head->val.INT=(int*)calloc(size,sizeof(int));
        break;
    case 1:
        head->val.FLOAT=(float*)calloc(size,sizeof(float));
        break;
    case 2:
        head->val.CHAR=(char*)calloc(size,sizeof(char));
        break;
    case 3:
        head->val.STRING=(char**)calloc(size,sizeof(char*));
        break;
    default:
        SementicError("error type");
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

