#include "elt.h"
int colom = 1, ligne = 1;

// Returns new Line
void newLine()
{
    ligne++;
    colom = 1;
    printf("\n%d-\t", ligne);
}
// Declare variables
element *listIDF = NULL, *listCONST = NULL; // IDF and CONST
elt *listKey = NULL /* Keywords */,
    *listSep = NULL /* Separators */,
    *listOperatorL = NULL /* Logical Operator */,
    *listOperatorA = NULL /* Arithmitci Operator */,
    *listType = NULL /* TYPES LIST*/,
    *listSPECIAL = NULL /* SPECIAL CHAR */,
    *listErrors = NULL /* SPECIAL CHAR */,
    *listComments = NULL /* COMMENTS*/;

void insert(char entity[], char type[], float val, int table)
{
    switch (table)
    {
    // Insert in IDF list
    case 0:
        push_elem(&listIDF, entity, type, val, 0);
        break;
    // Insert in Keywords list
    case 1:
        push_elt(&listKey, entity, type);
        break;
    // Insert in Separators list
    case 2:
        push_elt(&listSep, entity, type);
        break;
    // Insert in Logical Operator list
    case 3:
        push_elt(&listOperatorL, entity, type);
        break;
    // Insert in Arithmitic Operator list
    case 4:
        push_elt(&listOperatorA, entity, type);
        break;
    // Insert in Type list
    case 5:
        push_elt(&listType, entity, type);
        break;
    // Insert in Type list
    case 6:
        push_elem(&listCONST, entity, type, val, 0);
        break;
    // Insert in SPECIAL characters list
    case 7:
        push_elt(&listSPECIAL, entity, type);
        break;
    // Insert in Comments list
    case 8:
        push_elt(&listComments, entity, type);
        break;
    // Insert in ERRORS list
    case 9:
        push_elt(&listErrors, entity, type);
        break;
    }
}

void search(char entity[], char type[], float val, int table)
{
    colom = colom + strlen(entity);
    if (table < 8)
        printf("\033[0;35m|\033[0;37m %s : %s", type, entity);
    else if (table == 8)
    {
        // printf("\033[0;35m|\033[0;32m A Comment : %s\033[0;37m", entity);
        nTol(entity, &ligne, &colom);
    }
    else
        printf("\033[0;35m|\033[0;31mLexical Error %s \033[0;31m: %s  \033[0;37m ", type, entity);
    switch (table)
    {
    // search in IDF and CONST list
    case 0:
        if (!search_elem(listIDF, entity))
            insert(entity, type, val, table);
        break;
    // search in Keywords list
    case 1:
        if (search_elt(listKey, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Separators list
    case 2:
        if (search_elt(listSep, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Logical Operator list
    case 3:
        if (search_elt(listOperatorL, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Arithmitic Operator list
    case 4:
        if (search_elt(listOperatorA, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Type list
    case 5:
        if (search_elt(listType, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Constants list
    case 6:
        if (search_elem(listCONST, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Special characters list
    case 7:
        if (search_elt(listSPECIAL, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Special characters list
    case 8:
        if (search_elt(listComments, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Errors list
    case 9:
        if (search_elt(listErrors, entity) == 0)
            insert(entity, type, val, table);
        break;
    }
}

void print_TS()
{
    printf("------------------ IDF Table ------------------\n");
    print_elem(listIDF);

    printf("---------------------  Constants Table ------------------\n");
    print_elem(listCONST);

    printf("\n------------------ Keyword Table ------------------\n");
    print_elt(listKey);

    printf("\n------------------ Separators Symboles Table ------------------\n");
    print_elt(listSep);

    printf("\n------------------ Types Table ------------------\n");
    print_elt(listType);

    printf("\n------------------ Arithmitic Operators Symboles Table ------------------\n");
    print_elt(listOperatorA);

    printf("\n------------------ Logical Operators Symboles Table ------------------\n");
    print_elt(listOperatorL);

    printf("\n------------------ SPECIAL characters Table ------------------\n");
    print_elt(listSPECIAL);

    printf("\033[0;32m\n------------------ Comments Table ------------------\n");
    print_elt(listComments);

    printf("\033[0;31m\n------------------ Errors Table ------------------\n");
    print_Err(listErrors);
}