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

void AssignType(element *head,short Type,int Asize){
    if(head!=NULL){
        head->type=Type;
        head->size=Asize;
    }else
        SementicError("Variable couldn't be declared");
}
void AllocateData(element *head){
    int current=head->size;
    if(current==0)
        current++;
    switch (head->type)
    {
    case 0:
        head->val.INT=(int*)calloc(current,sizeof(int));
        break;
    case 1:
        head->val.FLOAT=(float*)calloc(current,sizeof(float));
        break;
    case 2:
        head->val.CHAR=(char*)calloc(current,sizeof(char));
        break;
    case 3:{
        head->val.STRING=(char**)calloc(current,sizeof(char*));
        
    }
        break;
    default:
        printf("error type");
        break;
    }
}