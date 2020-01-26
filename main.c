char *yytext;
#include "./MiniAcad/Lexical/Lexical.h"
List * Expression=NULL;



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
                case '+':
                case '-':
                case '/':
                case '*':
                    // oper
                    if(checker->val[0])
                    break;
                case '(':
                    //open
                    break;
                case ')':
                    //close
                    break;
                case 'm':

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