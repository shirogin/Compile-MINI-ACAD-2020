#include "element.h"
/* ----------------------------------------------------------------------------------------------------- */
        #define  printType "%s "
        typedef char* type;
/* ----------------------------------------------------------------------------------------------------- */
typedef struct Noed{
    type val;
    int Level;
    struct Noed * next;

}Noed;

typedef struct List{
    Noed *Head,
        *Tail;
}List;

void Init(List *list){
    list->Head=NULL;
    list->Tail=NULL;
}
Noed* CreatNoed(type VAL,int Level,Noed *next){
    Noed *X=(Noed*)malloc(sizeof(Noed));
    if(X==NULL){
        printf("allocation error in Noed");
        exit(-2);
    }
    X->val=(char*)malloc(strlen(VAL)*sizeof(char));
    if(X->val==NULL){
        printf("error allocation string");
        exit(-1);
    }
    strcpy(X->val,VAL);
    X->Level=Level;
    X->next=next;
    return X;
}
void Push(List **list,type VAL,int Level){
    if(*list==NULL){
        *list=(List*)malloc(sizeof(list));
        Init((*list));
    }
    Noed *newN=CreatNoed(VAL,Level,(*list)->Head);
    if((*list)->Head==NULL)
        (*list)->Tail=newN;
    (*list)->Head=newN;
}
void Pushf(List **list,type VAL,int Level){
    Noed *next=CreatNoed(VAL,Level,NULL);
    if(*list==NULL){
        *list=(List*)malloc(sizeof(list));
        Init((*list));
    }
    if((*list)->Tail!=NULL)
        (*list)->Tail->next=next;
    else 
        (*list)->Head=next;
    (*list)->Tail=next;
}
type Pop(List *list){
    Noed *tmp=list->Head;
    list->Head=tmp->next;
    if(list->Head==NULL)
        list->Tail=NULL;
    type val=tmp->val;
    free(tmp);
    return val;
}
type GetVal(List list){
    return list.Head->val;
}
int GetLevel(List list){
    return list.Head->Level;
}
int isEmpty(List list){
    if(list.Head==NULL)
        return 1;
    return 0;
}
void Print(List *list){
    if(list!=NULL){
        Noed *head=list->Head;
        while (head!=NULL)
        {
            fprintf(F,printType,head->val);
            head=head->next;
        }
    }
}