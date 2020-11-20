#include<stdio.h>
#include<assert.h>
#include "db.h"

int read_disk_block(void *);
void incr_lexptr(int *);
void decr_lexptr(int *);

int end_of_first_half(int);
int end_of_second_half(int);
int lexptr = 0;
int fwd = 0;
FILE * fp = NULL;

char dbuf[2 * SINGLE_BUF_SIZE];

void init_dbuf(const char * filename)
{
    dbuf[SINGLE_BUF_SIZE - 1] = EOF;
    dbuf[2*SINGLE_BUF_SIZE - 1] = EOF;
    fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "cannot open %s: no such file\n", filename);
    }
    read_disk_block(dbuf);

}

int read_disk_block(void * buf)
{
    assert(buf != NULL);
    size_t nchars = fread(buf, 1, DISK_BLK_SIZE, fp);
    if (nchars < DISK_BLK_SIZE)
    {
        *((char *)buf + nchars) = EOF;
        return (int) nchars + 1;

    }
    else
        return (int) nchars;
}

void get_lexeme(char * buf)
{
    int tmp = lexptr;
    int i = 0;
    while (tmp != fwd)
    {
        buf[i] = dbuf[tmp];
        incr_lexptr(&tmp);
        i++;
    }
    buf[i] = '\0';
    lexptr = fwd;
    if (dbuf[lexptr] == EOF)
    {
        incr_lexptr(&lexptr);
    }
}

void incr_lexptr(int * counter)
{
    ++(*(counter));
    switch (*counter)
    {
      case SINGLE_BUF_SIZE - 1:
        ++*counter;
        break;

      case 2 * SINGLE_BUF_SIZE - 1:
        *counter = 0;
        break;
      default:
        break;
    }
}

void retract(int n)
{
    //if n is equal to 0, it means push back everything that has been read
    //if n is equal to 1, push back the last character read

    switch (n)
    {
    case 0:
        fwd = lexptr;
        break;

    case 1:
        decr_lexptr(&fwd);
        break;
    }
}

void decr_lexptr(int * counter)
{

    --*counter;
    switch (*counter)
    {
    case SINGLE_BUF_SIZE - 1:
        --*counter;
        break;

    case 2 * SINGLE_BUF_SIZE - 1:
        --*counter;
        break;

    case -1:
        *counter = 2 * SINGLE_BUF_SIZE - 2; //go to the end of the second buffer just buffer the 2nd EOF
        break;
    }
}

int nextchar(void)  /* TODO: fix - "This function declaration is not a prototype" */
{
        int c = dbuf[fwd];
        if (c != EOF)
        {
            fwd++;
            return c;
        }
        if (end_of_first_half(fwd))
        {
            read_disk_block(dbuf + SINGLE_BUF_SIZE);
            ++fwd;
            c = dbuf[fwd];
            ++fwd;
            return c;
        }
        else if (end_of_second_half(fwd))
        {
            read_disk_block(dbuf);
            fwd = 0;
            c = dbuf[fwd];
            ++fwd;
            return c;
        }
        else   // indicates the end of the input file
        {
            return EOF;
        }
}

int end_of_first_half(int ptr)
{
    return ptr == SINGLE_BUF_SIZE-1;
}

int end_of_second_half(int ptr)
{
    return ptr == 2 * SINGLE_BUF_SIZE - 1;
}

void destroy_dbuf(void) /* TODO: fix - "This function declaration is not a prototype" */
{
    fclose(fp);
}
