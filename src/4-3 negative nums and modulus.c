#include <stdio.h>
#include <stdlib.h>         /* for atof() */
#define MAXOP   100         /* max size of operand or operator, which means you can't input a number with more than 100 digits */
#define NUMBER  '0'         /* signal that a number was found */

int     getop(char []);
void    push(double);
double  pop(void);

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
            op2 = pop();        /* get the LAST item from the stack */
            push(pop() - op2);  /* get the (previous) second to last item from stack */
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor\n");
            break;            
        case '\n':
            printf("\t%.8g\n", pop());
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
int numsign(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i = 0;      /* index for s */
    int c;          /* current character */
    int nc = 0;     /* next character */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';


    if (!isdigit(c) && c != '.')                                            /* if current char is not a number, then it could be an operator */
        if ((c=='+' || c=='-') && ((nc=getch()) == '.' || isdigit(nc))) {   /* ... or it could be the sign of an operand */
            c = nc;                                                         /* if the current char is an operand's sign, then skip it (it already is in s[]) */
            if (nc == '.')                                                  /* if the next character is a decimal dot, then add it to s[] */
                s[++i] = '.';
            else
                ungetch(nc);                                                /* else nc = (a number), and you don't wanna skip it, so you unget it */
        } else {
            if (nc != 0)                                                    /* nc got initialized in the if statement, this can happend when you get to a newline */
                ungetch(nc);
            return c;
        }


    if (isdigit(c))                             /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
           
    if (c == '.')                               /* collect fraction part */ 
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

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
