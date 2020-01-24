
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     IDF = 259,
     SIZE = 260,
     BEGI = 261,
     END = 262,
     var = 263,
     Let = 264,
     AFFECT = 265,
     EOI = 266,
     ATYPE = 267,
     ADDRESS = 268,
     IDFS = 269,
     OPENSEP = 270,
     TWOP = 271,
     CLOSESEP = 272,
     OPENBRACE = 273,
     CLOSEBRACE = 274,
     OPENBRACK = 275,
     CLOSEBRACK = 276,
     INT = 277,
     FLOATT = 278,
     CHART = 279,
     STRINGT = 280,
     INTEGER = 281,
     FLOAT = 282,
     CHAR = 283,
     STRING = 284,
     GET = 285,
     SHOW = 286,
     IF = 287,
     FOR = 288,
     RETURN = 289,
     ELSE = 290,
     END_IF = 291,
     END_FOR = 292,
     ADD = 293,
     SUB = 294,
     MUL = 295,
     DIV = 296,
     LOGIC_OP = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 32 "syntax.y"

    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;



/* Line 1676 of yacc.c  */
#line 103 "syntax.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


