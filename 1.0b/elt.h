#include "element.h"

typedef struct elt_t
{
    char *name;
    char *type;
    struct elt_t *next;
} elt;

void push_elt(elt **head, char name[], char type[])
{
    elt *new_node = (elt *)malloc(sizeof(elt));
    elt *last = *head;

    new_node->name = adapt(name);
    new_node->type = adapt(type);
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

void print_elt(elt *head)
{
    elt *current = head;

    while (current != NULL)
    {
        printf("Entity: %s  -  ", current->name);
        printf("Type: %s\n", current->type);
        current = current->next;
    }
}

void print_Err(elt *head)
{
    elt *current = head;
    if (current == NULL)
    {
        printf("there is No Error\n");
        return;
    }

    while (current != NULL)
    {
        printf("\033[0;31mLexical Error: %s  -  %s\n", current->name, current->type);
        current = current->next;
    }
}

int search_elt(elt *head, char name[])
{
    elt *current = head;
    int found = 0;

    while (current != NULL && !found)
    {
        if (strcmp(current->name, name) == 0)
            found = 1;
        current = current->next;
    }
    return found;
}