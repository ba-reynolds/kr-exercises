#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


/* ---------------------- STACK ---------------------- */
#define MAXSTACK 100
float stack[MAXSTACK];
int sindx = 0; /* stack index */

/* push: push a number to the stack */
void push(float n)
{
	if (sindx >= MAXSTACK)
		printf("push: error, stack overflow\n");
	else
		stack[sindx++] = n;
}

/* pop: pops the last number saved on the stack */
float pop()
{
	if (sindx == 0) {
		printf("pop: error, nothing to pop on the stack\n");
		return 0;
	}
	return stack[--sindx];
}
/* --------------------------------------------------- */



/* ----------------------- OPs ----------------------- */
#define NUMBER '0' /* value to signify that a number was returned */
/* getop: checks if s is a number, returns accordingly */
char getop(char *s)
{
	if (!isdigit(*s) && *s != '.')
		if ((*s == '+' || *s == '-') && isdigit(*(s+1)))
			return NUMBER;
		else
			return *s;
	return NUMBER;
}

/* opmenu: takes care of the operations to be done based on current op */
void opmenu(char op, char *s)
{
	int num2; /* number to store value for non-conmutative operations */
	
	switch (op) {
	case NUMBER:
		push(atof(s));
		break;
	case '+':
		push(pop() + pop());
		break;
	case '!':
		push(pop() * pop());
		break;
	case '-':
		num2 = pop();
		push(pop() - num2);
		break;
	case '/':
		num2 = pop();
		if (num2 == 0) {
			printf("opmenu: undefined division by zero\n");
			break;
		}
		push(pop() / num2);
		break;	
	default:
		printf("opmenu: use one of the following operators [+, !, -, /]\n");
		return;
	}
}
/* --------------------------------------------------- */


int main(int argc, char *argv[])
{
	while (*++argv)
		opmenu(getop(*argv), *argv);

	/* at this point *argv points to a null terminator */
	/* which means there's no more input left to read */
	printf("%f\n", pop());
}