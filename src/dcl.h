#ifndef __DCL_HEADER__
#define __DCL_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);

static int buf;
static int buffered = 0;

char* buffer;
int bufp = 0;
int getch(void);
void ungetch(int c);

int gettoken(void);    // type of last token


int tokentype;         // last token string
char token[MAXTOKEN];  // identifier name
char name[MAXTOKEN];
char datatype[MAXTOKEN]; // data type char, int, etc
char out[100];         // output string;

#endif