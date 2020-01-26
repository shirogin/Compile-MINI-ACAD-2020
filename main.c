char *yytext;
#include "./MiniAcad/Lexical/Lexical.h"
List * Expression=NULL;
int main(){
    Pushf(&Expression,"A");
    Pushf(&Expression,"=");
    Pushf(&Expression,"A");
    Pushf(&Expression,"+");
    Pushf(&Expression,"C");
    printf("work %s\n",Expression->Head->val);
    PrintL(Expression);
    return 0;
}