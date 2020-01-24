#include "OurString.h"

typedef struct element_t
{
    char *name;
    char *type;
    float val;
    int sub;
    struct element_t *next;
} element;

void push_elem(element **head, char name[], char type[], float val, int sub)
{
    element *new_node = (element *)malloc(sizeof(element));
    element *last = *head;

    new_node->name = adapt(name);
    new_node->type = adapt(type);
    new_node->val = val;
    new_node->sub = sub;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void append_elem(element **head, char name[], char type[], float val, int sub)
{
    element *new_node = (element *)malloc(sizeof(element));

    strcpy(new_node->name, name);
    strcpy(new_node->type, type);
    new_node->val = val;
    new_node->sub = sub;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    new_node->next = *head;

    *head = new_node;
}

int length_elem(element *head)
{
    int count = 0;
    element *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void print_elem(element *head)
{
    element *current = head;

    while (current != NULL)
    {
        fprintf(F,"Entity: %s  -  ", current->name);
        fprintf(F,"Type: %s", current->type);
        if ((strcmp(current->type, "FLOAT") == 0) || (strcmp(current->type, "INTEGER") == 0) || (strcmp(current->type, "CHAR") == 0) || (strcmp(current->type, "STRING") == 0))
            fprintf(F,"  -  Value: %f\n", current->val);
        else
            fprintf(F,"\n");
        current = current->next;
    }
}

int search_elem(element *head, char name[])
{
    element *current = head;
    int found = 0;

    while (current != NULL && !found)
    {
        if (strcmp(current->name, name) == 0)
            found = 1;
        current = current->next;
    }
    return found;
}