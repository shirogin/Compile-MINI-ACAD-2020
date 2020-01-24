%{
    #include "header.h"
    #include "syntax.tab.h"
    char str1[200],num[3];
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
SEPRATOR :|("||")|("(")|(")")|("{")|("}")
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
SIZE "["{INTEGER}"]"
ErrI ({letter}|{Digit})+
ErrCh (\'.+\')|('')
ErrS "«»"
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
{COMMENTS}  search(yytext,"COMMENTS",0,8);

{KEYWORD}   {
    search(yytext,"KEYWORD",0,1);
    switch(yytext[0]){
        case 'P':
            return (PROGRAM);
        case 'B':
            return (BEGI);
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
    search(yytext,"IDF",0,0);
    return (IDF);
}
{SEPRATOR} {
    search(yytext,"SEPRATOR ",0,2);
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
            return (OPENBRACK);
        case '}':
            return (CLOSEBRACK);
    }
} 
{AFFECT}   {
    search("=","AFFECTATION",0,2);
    return (AFFECT);
} 
{LOGIC_OP} {
    search(yytext,"Logical Operators",0,3);
    return (LOGIC_OP);
} 
{ARTH_OP}  { search(yytext,"Arithmetic Operators",0,4); 
    return (ARTH_OP);

}
{ATYPE} {search(yytext,"ARRAY TYPE",0,5);
    return (ATYPE);
}
{SIZE}      {
    sscanf(yytext,"[%d]",&size);
    search(yytext,"ARRAY SIZE",size,5);
    return (SIZE);
}
{TYPE}  {
    search(yytext,"TYPE",0,5);
    switch(yytext[0]){
        case 'C':
            return (CHART);
        case 'S':
            return (STRINGT);
        case 'F':
            return (FLOATT);
        case 'I':
            return (INT);
    }
}

    
{CHAR}      {
    yytext++;
    yytext[strlen(yytext)-1]='\0';
    search(yytext,"CHAR",yytext[1],6);
    return (CHAR);
}
{STRING}    {
    yytext=yytext+2;
    yytext[strlen(yytext)-2]='\0';
    search(yytext,"STRING",0,6);
    return (STRING);
}
{FLOAT}     {
    if(yytext[0]=='('){
        yytext++;
        yytext[strlen(yytext)-1]='\0';
    }
    search(yytext,"FLOAT",atof(yytext),6);
    return (FLOAT);
}
{INTEGER} {
    if(yytext[0]=='('){
        yytext++;
        yytext[strlen(yytext)-1]='\0';
    }
    search(yytext,"INTEGER",atoi(yytext),6);
    return (INTEGER);
}  
{SPECIAL}   {search(yytext,"SPECIAL",0,7);
    return (ADDRESS);
}
{EOI}       {
    search("£","EOI",0,7);
    return (EOI);
}
{SPACES}    {
    fprintf(F,"%s",yytext);
    colom= colom+ strlen(yytext);
}

{NL} newLine();
{ErrI} {
    sprintf(str1,"IDF must start with UpperCase character and have less than 8 character : ligne %d colom %d",ligne,colom);
    search(yytext,str1,0,9);
}
{ErrCh} {
    sprintf(str1,"characters must have one character : ligne %d colom %d",ligne,colom);
    search(yytext,str1,0,9);
}
{ErrS} {
    sprintf(str1,"Strings souldn't be empty : ligne %d colom %d",ligne,colom);
    search(yytext,str1,0,9);
}
{ErrC} {
    sprintf(str1,"Error in Comments : ligne %d colom %d",ligne,colom);
    search(yytext,str1,0,9);
}
{ErrU} {
    sprintf(str1,"ligne %d colom %d",ligne,colom);
    search(yytext,str1,0,9);
}
