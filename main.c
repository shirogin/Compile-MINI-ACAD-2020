char *yytext;
#include "./MiniAcad/Lexical/Lexical.h"
#include "./MiniAcad/syntaxic/QUAD.h"

List * Expression=NULL;
int qumtem=0;
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
//    Z - (-200.5) + (D * 5) £
int isOP (char *c){
        return (strcmp(c, "=" ) == 0 || strcmp(c, "+" ) == 0 || strcmp(c, "-" ) == 0 || strcmp(c, "*" )== 0 || strcmp(c, "/" ) == 0 || strcmp(c, "m" ) == 0);

}

qdr* qdrExpression(List *head){
    qdr *qdrs = NULL;
    List *pile;
    char res[10];

    while(!isEmpty(head)){
        char *c = GetVal(head);
        if (!isOP(c)){
            c = Pop(&head);
            Push(&pile, c);
        }else{
            char *op = Pop(&head);
            char *op2 = Pop(&pile);
            sprintf(res, "t%d", qumtem);
            qumtem++;
            switch(op[0]){
                case 'm':  {
                    Push(&pile, res);
                    push_qdr(&qdrs, "minus", op2, "", res);
                    break;
                }
                case '=': {
                    qumtem--;
                    char *op1 = Pop(&pile);
                    push_qdr(&qdrs, op, op1, "", op2);
                    break;
                }
                case '/':
                    if(strlen(op2)==1 && op2[0]=='0')
                        SementicError("Devision by 0");
                default: {
                    char *op1 = Pop(&pile);
                    Push(&pile, res);
                    push_qdr(&qdrs, op, op1, op2, res);
                    break;
                }
            }
            // if (strcmp(op, "m") == 0){
            //     Push(&pile, res);
            //     push_qdr(&qdrs, "minus", op1, "", res);
            // }else{
            //     char *op2 = Pop(&pile);
            //     Push(&pile, res);
            //     push_qdr(&qdrs, op, op1, op2, res);
            // }
        }
    }
    return qdrs;
}
int main(){
    Pushf(&Expression,"Z");
    Pushf(&Expression,"-");
    Pushf(&Expression,"-200.5");
    Pushf(&Expression,"+");
    Pushf(&Expression,"(");
    Pushf(&Expression,"D");
    Pushf(&Expression,"*");
    Pushf(&Expression,"5");
    Pushf(&Expression,")");


    PrintL(Expression);
    printf("\n");
    List *postfix=Postfix(Expression);

    PrintL(postfix);
    
    print_qdr(qdrExpression(postfix));
    printf("\n");
    return 0;
}