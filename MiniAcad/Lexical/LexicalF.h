
char *adapt(char tab[])
{
    char *s = (char *)malloc(sizeof(char) * strlen(tab));
    strcpy(s, tab);
    return s;
}

int nTol(char *s, int *line, int *col)
{
    int l = strlen(s), count = 0;
    for (int i = 0; i < l; i++)
    {
        if (s[i] == '\n')
        {
            (*line)++;
            fprintf(F,"\n%d-\t", *line);
            s[i] = '\t';
            *col = 1;
        }
        else
            fprintf(F,"%c", s[i]);
    }
    return count;
}
void newLine(){
    ligne++;
    colom = 1;
    fprintf(F,"\n%d-\t", ligne);
    free(Line);
    Line=NULL;
}

element* search_IDF(char name[]){
    return search_elem(listIDF,name);
}
element* search_CONST(char name[]){
    return search_elem(listCONST,name);
}

short getType(char name[]){
    element *current = search_elem(listIDF, name);
    if (current != NULL)
        return current->type;
    else{
        current = search_elem(listCONST, name);
        if (current != NULL)
            return current->type;
    }
    return -1;
}
void EVALUE(element *head,char *value,int index){
    switch (head->type)
    {
        case 0:
            head->val.INT[index]= atoi(value);
            break;
        case 1:
            head->val.FLOAT[index] = atof(value);
            break;
        case 2:
            head->val.CHAR[index]=value[0];
            break;
        case 3:
            head->val.STRING[index]=(char*)malloc(strlen(value)*sizeof(char));
            strcpy(head->val.STRING[index],value);
            break;
        default:
            SementicError("error type");
            break;
    }
}
void AssignConst(char *name,short Type,char *val){
    element *node = search_elem(listIDF, name);
    DATA VALUE;
    if (node != NULL){
        node->type = Type;
        AllocateData(node, 1);
        EVALUE(node,val,0);
    }
}
void SementicError(char *s){
    printf("\033[1;33mSementic Error in line %d  colom %d : %s \n\033[0m",ligne,colom-strlen(yytext),s);
    print_TS();
    exit(-1);
}
void Insert(char entity[],char* type,short Level){
    if(Line==NULL){
        Line=(char*)malloc(1000*sizeof(char));
        strcpy(Line,entity);
    }else
        strcat(Line,entity);
    colom = colom + strlen(entity);
    fprintf(F,"| %s : %s ", type, entity);
}
void CheckIDF(char entity[]){
    char d[100];
    if(Decalaration){
        if (search_elem(listIDF, entity)==NULL){
            push_elem(&listIDF,entity);
            return;
        }
        sprintf(d,"var '%s' is already declared",entity);
    }
    else if(search_elem(listIDF, entity)!=NULL)
        return;
    else
        sprintf(d,"this var '%s' isn't declared before",entity);
    SementicError(d);
}

void LexicalError(char *entity,char *type){
    if(Line==NULL){
        Line=(char*)malloc(1000*sizeof(char));
        strcpy(Line,entity);
    }else
        strcat(Line,entity);
    printf("\033[1;35mLexical Error %s : %s \n\033[0m", type, entity);
    fprintf(F,"|    Lexical Error %s : %s \n", type, entity);
}
void Comment(char *entity){
    fprintf(F,"| A Comment : ");
    nTol(entity, &ligne, &colom);
    Pushf(&listComments,entity);
}

void print_TS()
{
    fprintf(F,"\n------------------ IDF Table ------------------\n");
    print_elem(listIDF);

    fprintf(F,"\n------------------ Comments Table ------------------\n");
    Print(listComments);

}