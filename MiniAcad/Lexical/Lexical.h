#include "../Main.h"
//OUT put FILE
    FILE *F;
// Input Details
    int colom = 1, 
        ligne = 1,
        Decalaration = 1;// for var declaration
    char *Line;
//Symbole Table
    element *listIDF = NULL, //IDF list
        *listCONST=NULL;/* CONST list*/
    List *listComments = NULL /* COMMENTS*/;
#include "LexicalF.h"
#include "element.h"
#include "List.h"