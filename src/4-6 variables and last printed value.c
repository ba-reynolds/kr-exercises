#include <stdio.h>
#include <stdlib.h>         /* for atof() */
#define MAXOP   100         /* max size of operand or operator, which means you can't input a number with more than 100 digits */
#define NUMBER  '0'         /* signal that a number was found */

int     getop(char []);
void    push(double);
double  pop(void);
void    defvars(char s[]);
double  valvars(int c);

double _ = 0;           /* last value printed */

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
        case '#':       /* define variable */
            defvars(s);
            break;
        case '_':       /* print last value printed */
            push(_);
            break;
        
        default:
            if (type >= 'a' && type <= 'z') /* it's a variable */
                push(valvars(type));
            else
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
    if (sp > 0) {
        _ = val[--sp];
        return val[sp];
    }
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
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;                   /* not a number, but could be a variable */
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

#define ASCII_ALPHABET_LENGTH   26
#define ASCII_START_LOWER       'a'
#
double alphabet[ASCII_ALPHABET_LENGTH]; /* holds the value of each variable */

/* define variables from input */
void defvars(char s[])
{
    int var;
    int i;
    int c;

    while ((var=getch()) == ' ' || c == '\t')
        ;

    if (var >= 'a' &&  var <= 'z') {
        while ((s[0] = c = getchar()) != '\n' && !isdigit(c))
            ;
        i = 0;
        while ((s[++i] = c = getchar()) != '\n')
            ;
        s[i] = '\0';

        int alphabet_index = var - ASCII_START_LOWER;   /* index in the alphabet array */
        alphabet[alphabet_index] = atof(s);

    } else
        printf("vars: make sure your variable is within a-z\n");
}

double valvars(int c)
{
    return alphabet[c - ASCII_START_LOWER];
}
