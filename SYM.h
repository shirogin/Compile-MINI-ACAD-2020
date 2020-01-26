#include "QUAD.h"
void show(char *STRING,char *IDF,int index){
    element* el=search_IDF(IDF);
    if(el==NULL){
        SementicError("error show");
        return;
    }
    if(index>el->size){
        SementicError("INDEX out of BOUNDS");
        return;
    }
    int i=0;
    char c;
    while ((c=STRING[i])!='\0')
    {   
        switch (c)
        {
            case '$':
                printf("%d",el->val.INT[index]);
                break;
            case '%':
                printf("%f",el->val.FLOAT[index]);
                break;
            case '&':
                printf("%c",el->val.CHAR[index]);
                break;
            case '#':
                printf("%s",el->val.STRING[index]);
                break;
            default:
                printf("%c",c);
                break;
        }
        i++;
    }
    printf("\n");
}
void get(char *STRING,char *IDF,int index){
    element* el=search_IDF(IDF);
    if(el==NULL){
        SementicError("error show");
        return;
    }
    if(index>el->size){
        SementicError("INDEX out of BOUNDS");
        return;
    }
    if(el->size==0){
        SementicError("IDF is CONST(read only) You can't change it");
    }
    switch (STRING[0])
    {
        case '$':
            scanf("%d",&el->val.INT[index]);
            break;
        case '%':
            scanf("%f",&el->val.FLOAT[index]);
            break;
        case '&':
            scanf("%c",&el->val.CHAR[index]);
            break;
        case '#':
            scanf("%s",&el->val.STRING[index]);
            break;
        default:
            SementicError("Get can only read IDFS");
            break;
    }
}