#include "element.h"

int colom = 1, ligne = 1;

// Returns new Line
void newLine()
{
    ligne++;
    colom = 1;
    fprintf(F,"\n%d-\t", ligne);
}
// Declare variables
element *listIDF = NULL, *listCONST = NULL /* IDF and CONST*/,
    *listKey = NULL /* Keywords */,
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
        push_elem(&listKey, entity, type, val, 0);
        break;
    // Insert in Separators list
    case 2:
        push_elem(&listSep, entity, type, val, 0);
        break;
    // Insert in Logical Operator list
    case 3:
        push_elem(&listOperatorL, entity, type, val, 0);
        break;
    // Insert in Arithmitic Operator list
    case 4:
        push_elem(&listOperatorA, entity, type, val, 0);
        break;
    // Insert in Type list
    case 5:
        push_elem(&listType, entity, type, val, 0);
        break;
    // Insert in Type list
    case 6:
        push_elem(&listCONST, entity, type, val, 0);
        break;
    // Insert in SPECIAL characters list
    case 7:
        push_elem(&listSPECIAL, entity, type, val, 0);
        break;
    // Insert in Comments list
    case 8:
        push_elem(&listComments, entity, type, val, 0);
        break;
    // Insert in ERRORS list
    case 9:
        push_elem(&listErrors, entity, type, val, 0);
        break;
    }
}

void search(char entity[], char type[], float val, int table)
{
    colom = colom + strlen(entity);
    if (table < 8)
        fprintf(F,"| %s : %s ", type, entity);
    else if (table == 8)
    {
        // fprintf(F,"\033[0;35m|\033[0;32m A Comment : %s\033[0;37m", entity);
        nTol(entity, &ligne, &colom);
    }
    else
        fprintf(F,"| Lexical Error %s : %s ", type, entity);
    switch (table)
    {
    // search in IDF and CONST list
    case 0:
        if (!search_elem(listIDF, entity))
            insert(entity, type, val, table);
        break;
    // search in Keywords list
    case 1:
        if (search_elem(listKey, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Separators list
    case 2:
        if (search_elem(listSep, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Logical Operator list
    case 3:
        if (search_elem(listOperatorL, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Arithmitic Operator list
    case 4:
        if (search_elem(listOperatorA, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Type list
    case 5:
        if (search_elem(listType, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Constants list
    case 6:
        if (search_elem(listCONST, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Special characters list
    case 7:
        if (search_elem(listSPECIAL, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Special characters list
    case 8:
        if (search_elem(listComments, entity) == 0)
            insert(entity, type, val, table);
        break;
    // search in Errors list
    case 9:
        if (search_elem(listErrors, entity) == 0)
            insert(entity, type, val, table);
        break;
    }
}

void print_TS()
{
    fprintf(F,"\n------------------ IDF Table ------------------\n");
    print_elem(listIDF);

    fprintf(F,"---------------------  Constants Table ------------------\n");
    print_elem(listCONST);

    fprintf(F,"\n------------------ Keyword Table ------------------\n");
    print_elem(listKey);

    fprintf(F,"\n------------------ Separators Symboles Table ------------------\n");
    print_elem(listSep);

    fprintf(F,"\n------------------ Types Table ------------------\n");
    print_elem(listType);

    fprintf(F,"\n------------------ Arithmitic Operators Symboles Table ------------------\n");
    print_elem(listOperatorA);

    fprintf(F,"\n------------------ Logical Operators Symboles Table ------------------\n");
    print_elem(listOperatorL);

    fprintf(F,"\n------------------ SPECIAL characters Table ------------------\n");
    print_elem(listSPECIAL);

    fprintf(F,"\n------------------ Comments Table ------------------\n");
    print_elem(listComments);

    fprintf(F,"\n------------------ Errors Table ------------------\n");
    print_elem(listErrors);
}