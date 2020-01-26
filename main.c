char *yytext;
#include "./MiniAcad/Lexical/Lexical.h"
List * Expression=NULL;

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
    case '(':
    case ')':
        return 3;
    default:
        return 0;
        break;
    }
}

List * Postfix(List *expression){
    List *postfix =NULL;
    Noed *checker=expression->Head;
    List *operators=NULL;
    while (checker!=NULL)
    {
        printf("1\n");
        if(strlen(checker->val)>1){
            Pushf(&postfix,checker->val);
        }else
        {
            switch (checker->val[0])
            {
                case '=':
                case '+':
                case '-':
                case '/':
                case '*':
                    // oper
                    if(operators!=NULL && !isEmpty(operators)){
                        if(Value(checker->val) <= Value(GetVal(operators)) )
                            Pushf(&expression,Pop(&operators));
                    }
                    Push(&operators,checker->val);
                    break;
                case '(':
                    //open
                    Push(&operators,"(");
                    break;
                case ')':
                    //close
                    if(operators!=NULL)
                    while (!isEmpty(operators) && (GetVal(operators)[0]!='('))
                    {
                        Pushf(&postfix,Pop(&operators));
                    }
                    Pop(&operators);
                    break;
                case 'm':
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
int main(){
    Pushf(&Expression,"A");
    Pushf(&Expression,"=");
    Pushf(&Expression,"B");
    Pushf(&Expression,"+");
    Pushf(&Expression,"C");
    Pushf(&Expression,"*");
    Pushf(&Expression,"C");
    Pushf(&Expression,"-");
    Pushf(&Expression,"D");
    Pushf(&Expression,"*");
    Pushf(&Expression,"10");
    PrintL(Expression);
    printf("\n");
    List *postfix=Postfix(Expression);
    PrintL(postfix);
    printf("\n");

    return 0;
}