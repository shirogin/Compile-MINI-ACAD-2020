void Init(List *list){
    list->Head=NULL;
    list->Tail=NULL;
}
Noed* CreatNoed(type VAL,Noed *next){
    Noed *X=(Noed*)malloc(sizeof(Noed));
    if(X==NULL){
        printf("allocation error in Noed");
        exit(-2);
    }
    X->val=adapt(VAL);
    X->next=next;
    return X;
}
void Push(List **list,type VAL){
    if(*list==NULL){
        *list=(List*)malloc(sizeof(list));
        Init((*list));
    }
    Noed *newN=CreatNoed(VAL,(*list)->Head);
    if((*list)->Head==NULL)
        (*list)->Tail=newN;
    (*list)->Head=newN;
}
void Pushf(List **list,type VAL){
    Noed *next= CreatNoed(VAL,NULL);
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
type Pop(List **list){
    Noed *tmp=(*list)->Head;
    (*list)->Head=tmp->next;
    if((*list)->Head==NULL)
        (*list)->Tail=NULL;
    type val=tmp->val;
    free(tmp);
    return val;
}
type GetVal(List *list){
    return list->Head->val;
}
int isEmpty(List *list){
    if(list->Head==NULL)
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