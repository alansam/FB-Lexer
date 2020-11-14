///symtab.c//

#include <stdio.h>
#include <stdlib.h> /* <malloc.h> */
#include <string.h>
#include "symtab.h"

static symtab_entry_t * g_symlist = NULL;

symtab_entry_t * newnode(symtype_t t,const char * lex, int line, int token)
{
    symtab_entry_t *new  = (symtab_entry_t *)malloc(sizeof(symtab_entry_t));
    new->type = t;
    strcpy(new->lexeme, lex);
    new->lineno = line;
    new->token = token;
    new->next = NULL;
    return new;
}

void symtab_create(void) /* TODO: fix - "This function declaration is not a prototype" */
{
    g_symlist = newnode(HEADER, " ", 0, 0);
}

symtab_entry_t * symtab_insert(symtype_t t,const char * lex, int line, int token)
{
    symtab_entry_t *new = newnode(t, lex, line, token);
    if (g_symlist->next == NULL)
    {
        g_symlist->next = new;
    }
    else
    {
         symtab_entry_t *ele = NULL;
         for (ele = g_symlist->next; ele->next != NULL; ele = ele->next);
         ele->next = new;
    }
    return new;
}

static char *type_str[] = { "HEADER", "RELATIONAL OPERATOR", "NUMBER", "VARIABLE", "KEYWORD"};

void symtab_print_entry(symtab_entry_t *ele)
{
    printf("Lexeme = %s\n", ele->lexeme);
    printf("Type = %s\n", type_str[ele->type]);
    printf("Line no = %d\n", ele->lineno);
    printf("Token no  = %d\n", ele->token);
}

void symtab_print(void) /* TODO: fix - "This function declaration is not a prototype" */
{
    symtab_entry_t *ele = NULL;
    for (ele = g_symlist->next; ele != NULL; ele = ele->next)
    {
        symtab_print_entry(ele);
    }
}

symtab_entry_t * symtab_lookup(const char *lex)
{
    symtab_entry_t *ele = NULL;
    for (ele = g_symlist->next; ele != NULL; ele = ele->next)
    {
        if (strcmp(ele->lexeme, lex) == 0)   //Checking if the lexeme already exists in the symbol table
        {
            return ele;
        }
    }
    return 0;
}
