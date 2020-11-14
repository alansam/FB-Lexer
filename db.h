#ifndef MY_DB_H
#define MY_DB_H

#define DISK_BLK_SIZE 512
#define SINGLE_BUF_SIZE DISK_BLK_SIZE+1
extern int fwd;
void init_dbuf(const char*);
int nextchar(void);   /* TODO: fix - "This function declaration is not a prototype" */
void incr_lexptr(int *);
void retract(int);
void get_lexeme(char *);
void destroy_dbuf(void);  /* TODO: fix - "This function declaration is not a prototype" */
#endif // MY_DB_H
