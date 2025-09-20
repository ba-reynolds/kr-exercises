#include <stdio.h>
#include <stdlib.h>         /* for atof() */
#define MAXOP   100         /* max size of operand or operator, which means you can't input a number with more than 100 digits */
#define NUMBER  '0'         /* signal that a number was found */

int     getop(char []);
void    push(double);
double  pop(void);

void    prntlast(void);
void    duplast(void);
void    swaptwo(void);
void    clear(void);
void    len(void);
void    full(void);

/* reverse Polish calculator */
int main()
{
    int     type;
    char    s[MAXOP];
    double  op2;
    
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();        /* get the last item from the stack */
            push(pop() - op2);  /* get the (previous) second to last item from stack */
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        /* start of commands to modify the stack */
        case 'p':
            prntlast();
            break;
        case 'd':
            duplast();
            break;
        case 's':
            swaptwo();
            break;
        case 'c':
            clear();
            break;
        case 'l':
            len();
            break;
        case 'f':
            full();
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100      /* maximum depth of val stack */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
} 


#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    
    int i, c;
    int nc = 0;     /* next character */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.') {
        return c;                   /* not a number */
    }
    i = 0;
    if (isdigit(c))                 /* collect integer part */
        while (isdigit(s[++i] = c = getch()))   /* 'i' gets updated here even with a single digit num like 4 */
            ;
    if (c == '.') /* collect fraction part */ 
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';                                /* which is why this doesn't overwrite a single digit number */

    if (c != EOF)
        ungetch(c);
    return NUMBER;
} 

#define BUFSIZE 100
char buf[BUFSIZE];              /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

int getch(void)                 /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp]: getchar();
}

void ungetch(int c)             /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
} 

/* print the last stack element without popping it. gets called with 'p' */
void prntlast(void)
{
    /* ctrl + z esta jodido no arreglar */

    while (getch() != '\n')   /* skip newline so it won't pop the last stack element */
        ;
    if (sp == 0)
        printf("pstack: the stack is currently empty\n");
    else 
        printf("pstack: last stack element %.f\n", val[sp-1]);
}

/* duplicates the last stack element. gets called with 'd'*/
void duplast(void)
{
    while (getch() != '\n')
        ;    
    if (sp > 0) {
        val[sp] = val[sp++-1];
        printf("duplast: duplicated %.f\n", val[sp-1]);
    } else
        printf("duplast: the stack is currently empty, can't duplicate\n");

}

/* swap position between the last two elements. gets called with 's' */
void swaptwo(void)
{
    while (getch() != '\n')
        ;
    if (sp > 1) {
        int temp;
        temp        = val[sp-1];
        val[sp-1]     = val[sp-2];
        val[sp-2]   = temp;
        printf("swaptwo: swapped %.f with %.f\n", val[sp-1], val[sp-2]);
    } else
        printf("swaptwo: the stack is currently empty or there are less than two elements, cant swap\n");
}

/* clears the stack. gets called with 'c' */
void clear(void)
{
    while (getch() != '\n')
        ;
    if (sp > 0) {
        while (sp != 0)
            val[--sp] = 0;
        printf("clear: cleared the entire stack\n");
    } else
        printf("clear: the stack is currently empty, can't clear\n");
}

/* prints the current length of the stack */
void len(void)
{
    while (getch() != '\n')
        ;    
    printf("len: the current stack len is: %i\n", sp);
}

/* prints the entire stack in a python-esque way */
void full(void)
{
    while (getch() != '\n')
        ;
    
    int i;
    printf("[");
    for (i=0; i<sp; ++i)
        printf("%.f, ", val[i]);
    printf("%s]\n", (sp>0) ? "\b\b": "");

}