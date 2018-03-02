#include "dcl.h"

// dcl: parse a declarator
void
dcl(void) {
	int ns;

	// count the number of *'s
	for (ns = 0; gettoken() == '*'; )
		ns++;

	dirdcl();

	while (ns-- > 0)
		strcat(out, " pointer to");
}

void
dirdcl(void) {
	int type;
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
		}
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int
gettoken(void) {
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t') {}
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;

	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}


int getch()
{
	if (buffered) {
		buffered = 0;
		return buf;
	}
	return getchar();
}

void ungetch(int c) {
	buffered = 1;
	buf = c;
}

int
main(int argc, char** argv) {
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
			printf("Syntax Error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
}