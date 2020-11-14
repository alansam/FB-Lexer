#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "db.h"
#include "symtab.h"
#include "lexer.h"

#define MAX_YYTEXT_SIZE 256

int start = 0;
int state = 0;
int lc = 1; //line count

char text[MAX_YYTEXT_SIZE];

char * yytext = text;

valtype_t yyval; //this contains the value of the current lexeme

void lexer_accept(void) /* TODO: fix - "This function declaration is not a prototype" */
{
    start = 0;
    state = 0;
    get_lexeme(yytext);
}

int fail(void)  /* TODO: fix - "This function declaration is not a prototype" */
{
  switch (start)
  {
    case 0:
      retract(0);
      start = 9;
      break;
    case 9:
      retract(0);
      start = 12;
      break;
    case 12:
      start = 100;
      break;

    default:assert(0);
      break;
  }
  return start;
}

int yylex(void) /* TODO: fix - "This function declaration is not a prototype" */
{
  int c;
  while (1)  //infinite loop
  {
    switch (state)
    {
      case 0:
        c = nextchar();
        if (c == EOF)
        {
          return EOF;
        }
        if (isspace(c))
        {
          incr_lexptr(&fwd);
          if (c == '\n') ++lc;
        }
         else
         {
           switch (c)
           {
             case '<':
               state =1;
               break;

             case '=':
               state = 5;
               break;

             case '>':
               state = 6;
               break;
         
             default:
               state = fail();
               break;
           }
         }
         break;

      case 1:
           c = nextchar();
           switch (c)
           {
             case '=':
               state = 2;
               break;

             case '>':
               state = 3;
               break;

             default:
               state = fail();
               break;
           }

      case 2:
        lexer_accept();
        return LE;

      case 3:
        lexer_accept();
        return NE;

      case 4:
        retract(1);
        lexer_accept();
        return LT;

      case 5:
        lexer_accept();
        return EQ;

      case 6:
        c = nextchar();
        switch (c)
        {
          case '=':
            state = 7;
            break;

          default:
            state = 8;
            break;
        }

      case 7:
        lexer_accept();
        return GE;

      case 8:
        retract(1);
        lexer_accept();
        return GT;

      case 9:
        c = nextchar();
        if (isalpha(c)) state = 10;
        else state = fail();
        break;

      case 10:
        c = nextchar();
        if (isalnum(c)) state =  10;
        else state = 11;
        break;

      case 11:
        retract(1);
        lexer_accept();
        symtab_entry_t *ele = symtab_lookup(yytext);
        if (!ele)
        {
          ele = symtab_insert(VARIABLE,yytext,lc,ID);
        }
        yyval.sval = ele;
        return ele->token;

      case 12:
        c = nextchar();
        if (isdigit(c)) state = 13;
        else state = fail();
        break;

      case 13:
        c = nextchar();
        if (isdigit(c)) state = 13;
        else if ( c == '.') state = 14;
        else if ( c == 'e') state = 16;
        else state = 20;
        break;

      case  14:
        c = nextchar();
        if (isdigit(c)) state = 15;
        else state = fail();
        break;

      case 15:
        c = nextchar();
        if (isdigit(c)) state = 15;
        else if (c == 'e') state = 16;
        else state = 21;
        break;

      case 16:
        c = nextchar();
        if( c == '+' || c == '-') state  = 17;
        else if (isdigit(c)) state = 18;
        else state = fail();
        break;

      case 17:
        c = nextchar();
        if (isdigit(c)) state = 18;
        else state = fail();
        break;

      case 18:
        c = nextchar();
        if (isdigit(c)) state = 18;
        else state = 19;
        break;

      case 19:
        retract(1);
        lexer_accept();
        yyval.dval = atof(yytext);
        return FLOAT;
        break;

      case 20:
        retract(1);
        lexer_accept();
        yyval.ival =  atoi(yytext);
        return INT;
        break;

      case 21:
        retract(1);
        lexer_accept();
        yyval.dval = atof(yytext);
        return FLOAT;
        break;

      case 100:
        lexer_accept();
        return ERROR;

      default:
        assert(0);
        break;
    } //end of switch
  } //end of while()
    
} //end of yylex()
