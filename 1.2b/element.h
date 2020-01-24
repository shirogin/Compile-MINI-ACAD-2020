#include "OurString.h"

typedef union DATA
{
    int INT,
        INTARRAY,
        *const CONSTINT;
    float FLOAT,
        FLOATARRAY,
        *const CONSTFLOAT;
    char CHAR,
        *const CONSTCHAR;
    char *STRING,
        *const CONSTSTRING,
        *CHARARRAY,
        **STRINGARRAY;
}DATA;
typedef struct element_t
{
    char *name;
    int type;
    DATA val;
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