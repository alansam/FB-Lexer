#include <stdio.h>
#include <assert.h>
#include "db.h"
#include "symtab.h"
#include "lexer.h"

void load_keywords()
{
    symtab_create();
    symtab_insert(KEYWORD, "if", 0, IF);
    symtab_insert(KEYWORD, "else", 0, ELSE);
    symtab_insert(KEYWORD, "then", 0, THEN);
}

void yyparse()
{
    int token;
    while ((token = yylex()) != EOF)
    {
        // printf("token =  %d\n",token);
        switch (token)
        {
          case INT:
            printf("ival= %d\n", yyval.ival);
            break;

          case FLOAT:
            printf("dval = %f\n", yyval.dval);
            break;

          case ID:
            symtab_print_entry(yyval.sval);
            break;
        
          default:
            break;
        }
    }
}

#if defined(AS_NEED_MAIN_)
int main()
#else
int parser_main(void)
#endif
{
    const char * filename = "./test.txt";
    init_dbuf(filename);
    load_keywords();
    yyparse();
    destroy_dbuf();
    return 0;

}
