void show(char *STRING,char *IDF,int index)
{
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
void get(char *STRING,char *IDF,int index)
{
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
short Value(char *x){
    switch (x[0])
    {
        case '=':
            return 0;
            break;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
            break;
    }
}

List * Postfix(List *expression){
    List *postfix =NULL;
    Noed *checker=expression->Head;
    List *operators=NULL;
    char *s;

    while (checker!=NULL)
    {
        if(strlen(checker->val)>1){
            Pushf(&postfix,checker->val);
        }else{
            switch (checker->val[0])
            {
                case '=':
                case '+':
                case '-':
                case '/':
                case '*':
                    // oper
                    if(operators!=NULL && !isEmpty(operators)){
                        if( Value(checker->val) <= Value(GetVal(operators)) )
                            Pushf(&postfix,Pop(&operators));
                    }
                    Push(&operators,checker->val);
                    break;
                case '(':
                    //open
                    Push(&operators,"(");
                    break;
                case ')':
                    //close
                    while (!isEmpty(operators) && ((s=Pop(&operators))[0]!='('))
                    {
                        Pushf(&postfix,s);
                    }
                    break;
                case 'm':
                    checker=checker->next;
                    Pushf(&postfix,checker->val);
                    Pushf(&postfix,"m");
                    break;
                default:
                    //error
                    Pushf(&postfix,checker->val);
                    break;
            }
        }  
        checker=checker->next;
    }
    
    while (operators!=NULL && (!isEmpty(operators)))
    {
        Pushf(&postfix,Pop(&operators));
    }
    
    return postfix;
}
int isOP (char *c){
    return ( c[0]=='=' || c[0]=='+' || c[0]=='-' || c[0]=='*' || c[0]=='/' || c[0]=='m' );
}

qdr* qdrExpression(List *head){
    qdr *qdrs = NULL;
    int i = 0;
    List *pile;
    while(!isEmpty(head)){
        char *c = GetVal(head);
        if (!isOP(c)){
            c = Pop(&head);
            Push(&pile, c);
        }else{
            char *op = Pop(&head);
            char *op1 = Pop(&pile);
            char res[100];
            sprintf(res, "t%d", i);
            i++;
            if (strcmp(op, "m") == 0){
                Push(&pile, res);
                push_qdr(&qdrs, "minus", op1, "", res);
            }else{
                char *op2 = Pop(&pile);
                Push(&pile, res);
                push_qdr(&qdrs, op, op1, op2, res);
            }
        }
    }
    return qdrs;
}
