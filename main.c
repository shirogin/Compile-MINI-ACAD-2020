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
        if(strlen(checker->val)>1){
            Pushf(&postfix,"dd");
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
                    if(Value(checker->val)<=Value(GetVal(operators)))
                        
                    break;
                case '(':
                    //open
                    Push(&operators,"(");
                    break;
                case ')':
                    //close
                    while (!isEmpty(operators))
                    {

                    }
                    
                    break;
                case 'm':
                    Push(&postfix,"m");
                    break;
                default:
                    //error
                    break;
            }
        }
        
        checker=checker->next;
    }
    
}
int main(){
    Pushf(&Expression,"A");
    Pushf(&Expression,"=");
    Pushf(&Expression,"A");
    Pushf(&Expression,"+");
    Pushf(&Expression,"C");
    PrintL(Expression);
    printf("work \n");
    return 0;
}