#ifndef MY_LEXER_H
#define MY_LEXER_H

#include "symtab.h"

#define ERROR 256
#define LT 257
#define LE 258
#define EQ 259
#define NE 260
#define GT 261
#define GE 262
#define ID 263
#define INT 264
#define FLOAT 265
#define IF 266
#define THEN 267
#define ELSE 268

extern
char * yytext;

typedef union vtype
{
    int ival;
    double dval;
    symtab_entry_t *sval;
} valtype_t;

extern
valtype_t yyval; //this contains the value of the current lexeme

int yylex(void);  /* TODO: fix - "This function declaration is not a prototype" */

#endif
