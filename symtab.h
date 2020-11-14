#ifndef MY_SYMTAB_H
#define MY_SYMTAB_H
#define MAX_BUF_SIZE 100

typedef enum {HEADER =0, RELOP, NUMBER, VARIABLE, KEYWORD} symtype_t;

typedef struct sym_entry
{
    symtype_t type;
    char lexeme[MAX_BUF_SIZE];
    int lineno;
    struct sym_entry *next;
    int token;
} symtab_entry_t;

symtab_entry_t * newnode(symtype_t, const char *, int, int);
void symtab_create(void); /* TODO: fix - "This function declaration is not a prototype" */
symtab_entry_t * symtab_insert(symtype_t, const char *, int, int);
symtab_entry_t * symtab_lookup(const char *);
void symtab_print_entry(symtab_entry_t *);
void symtab_print(void);  /* TODO: fix - "This function declaration is not a prototype" */

#endif
