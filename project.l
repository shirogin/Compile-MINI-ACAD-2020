%{
    #include "Lexical.h"
    #include "syntax.tab.h"
    char str1[200];
    int size;
%}
lettreM [A-Z]
lettrem [a-z]
letter {lettreM}|{lettrem}
SPACES [ \t]+
Digit [0-9]
INTEGER ("("("+"|"-"){Digit}+")")|{Digit}+
FLOA {Digit}+"."{Digit}+
FLOAT ("("("+"|"-"){FLOA}")")|{FLOA}
EOI "£"
SPECIAL "@"
SEPRATOR :|("||")|("(")|(")")|("{")|("}")|("[")|("]")
AFFECT "="
CHAR \'.\'
STRING "«".+"»"
TYPE (INT)|(FLOAT)|(CHAR)|(STRING)
ATYPE "["{TYPE}"]"
KEYWORD (PROGRAM)|(BEGIN)|(END)|(var)|(Let)|(GET)|(SHOW)|(IF)|(ELSE)|(RETURN)|(FOR)|(END_FOR)|(END_IF)
IDF {lettreM}({lettrem}|{Digit}){0,7}
ARTH_OP [+-/*]
LOGIC_OP (<<)|(>>)|(<<>>)|(<<=)|(>>=)|(==)
NL (\r\n)|(\n)
COMMENTS "//"(([^/]|\n)|("/"([^/]+|\n)))*"//"
SIZE "["{Digit}+"]"
ErrI ({letter}|{Digit})+
ErrCh (\'.+\')|('')
ErrS «([^»]|{NL})*»?
ErrC ("//".+)
ErrU (.)
/* Tabels
    * 0- IDF
    * 1- Keyword
    * 2- Separators
    * 3- Logical Operator
    * 4- Arithmitic Operator
    * 5- Types
    * 6- Constants
*/
%%
{COMMENTS} {
    Comment(yytext);
}  

{KEYWORD}   {
    Insert(yytext,"KEYWORD",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    switch(yytext[0]){
        case 'P':
            return (PROGRAM);
        case 'B':{
            Decalaration=0;
            return (BEGI);
        }
        case 'E':{
            if(strcmp(yytext,"ELSE") == 0)
                return (ELSE);
            else if(strcmp(yytext,"END_FOR") == 0)
                return (END_FOR);
            else if(strcmp(yytext,"END_IF") == 0)
                return (END_IF);
            else if(strcmp(yytext,"END") == 0)
                return (END);
        }
        case 'v':
            return (var);
        case 'L':
            return (Let);
        case 'G':
            return (GET);
        case 'S':
            return (SHOW);
        case 'I':
            return (IF);
        case 'F':
            return (FOR);
        case 'R':
            return (RETURN);
    }
}
{IDF}   {
    Insert(yytext,"IDF",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    CheckIDF(yytext);
    return (IDF);
}
{SEPRATOR} {    
    Insert(yytext,"SEPRATOR",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    switch(yytext[0]){
        case '|':
            return (IDFS);
        case '(':
            return (OPENSEP);
        case ':':
            return (TWOP);
        case ')':
            return (CLOSESEP);
        case '{':
            return (OPENBRACE);
        case '}':
            return (CLOSEBRACE);
        case '[':
            return (OPENBRACK);
        case ']':
            return (CLOSEBRACK);
    }
} 
{AFFECT}   {
    Insert(yytext,"AFFECT",0);
    yylval.myCHAR=yytext[0];
    return (AFFECT);
} 
{LOGIC_OP} {
    Insert(yytext,"LOGIC_OP",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    return (LOGIC_OP);
} 
{ARTH_OP}  { 
    Insert(yytext,"ARTH_OP",0);
    sscanf(yytext,"%s",yylval.mySTRING);

    switch(yytext[0]){
        case '+':
            return (ADD);
        case '-':
            return (SUB);
        case '*':
            return (MUL);
        case '/':
            return (DIV);
    }
}
{ATYPE} {
    Insert(yytext,"ATYPE",0);
    yytext++;
    yytext[strlen(yytext)-1]='\0';
    switch(yytext[0]){
        case 'I':{
            yylval.myINT=0;
            return (ITYPE);
        }break;
        case 'F':{
            yylval.myINT=1;
            return (FTYPE);
        }break;
        case 'C':{
            yylval.myINT=2;
            return (CTYPE);
        }break;
        case 'S':{
            yylval.myINT=3;
            return (STYPE);
        }break;
    }
}
{SIZE}      {
    Insert(yytext,"SIZE",0);
    yytext++;
    yytext[strlen(yytext)-1]='\0';
    yylval.myINT=atoi(yytext);
    return (SIZE);
}
{TYPE}  {
    Insert(yytext,"TYPE",0);
    switch(yytext[0]){
        case 'I':{
            yylval.myINT=0;
            return (ITYPE);
        }break;
        case 'F':{
            yylval.myINT=1;
            return (FTYPE);
        }break;
        case 'C':{
            yylval.myINT=2;
            return (CTYPE);
        }break;
        case 'S':{
            yylval.myINT=3;
            return (STYPE);
        }break;
    }
}

    
{CHAR} {
    Insert(yytext,"CHAR",0);
    yytext++;
    yytext[strlen(yytext)-1]='\0';
    pushELEM(&listCONST,yytext,2);
    sscanf(yytext,"%s",yylval.mySTRING);
    return (CHAR);
}
{STRING} {
    Insert(yytext,"STRING",0);
    yytext=yytext+2;
    yytext[strlen(yytext)-2]='\0';
    pushELEM(&listCONST,yytext,3);
    strcpy(yylval.mySTRING,yytext);
    return (STRING);
}
{FLOAT}     {
    if(yytext[0]=='('){
        yytext++;
        yytext[strlen(yytext)-1]='\0';
    }
    pushELEM(&listCONST,yytext,1);
    Insert(yytext,"FLOAT",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    return (FLOAT);
}
{INTEGER} {
    if(yytext[0]=='('){
        yytext++;
        yytext[strlen(yytext)-1]='\0';
    }
    pushELEM(&listCONST,yytext,0);
    Insert(yytext,"INTEGER",0);
    sscanf(yytext,"%s",yylval.mySTRING);
    return (INTEGER);
}  
{SPECIAL}   {
    Insert(yytext,"SPECIAL",0);
    yylval.myCHAR=yytext[0];
    return (ADDRESS);
}
{EOI}       {
    Insert(yytext,"EOI",0);
    yylval.myCHAR=yytext[0];
    return (EOI);
}
{SPACES}    {
    fprintf(F,"%s",yytext);
    colom= colom+ strlen(yytext);
    if(Line==NULL){
        Line=(char*)malloc(1000*sizeof(char));
        strcpy(Line,yytext);
    }else
        strcat(Line,yytext);
}

{NL} newLine();
{ErrI} {
    sprintf(str1,"IDF must start with UpperCase character and have less than 8 character : ligne %d colom %d",ligne,colom);
    LexicalError(yytext,str1);
}
{ErrCh} {
    sprintf(str1,"characters must have one character : ligne %d colom %d",ligne,colom);
    LexicalError(yytext,str1);
}
{ErrS} {
    sprintf(str1,"Strings souldn't be empty : ligne %d colom %d",ligne,colom);
    LexicalError(yytext,str1);
}
{ErrC} {
    sprintf(str1,"Error in Comments : ligne %d colom %d",ligne,colom);
    LexicalError(yytext,str1);
}
{ErrU} {
    sprintf(str1,"unknown error ligne %d colom %d",ligne,colom);
    LexicalError(yytext,str1);
}
