#include <stdio.h>
#include <stdlib.h>         /* for atof() */
#define MAXOP   100         /* max size of operand or operator, which means you can't input a number with more than 100 digits */
#define NUMBER  '0'         /* signal that a number was found */

int     getop(char []);
void    push(double);
double  pop(void);

/* cruck <- true */

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
        default:
            printf("\nTEST...%d...\n", type);
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



#define MAXINPUT 100            /* max length for input */
int line[MAXINPUT];             /* where input will be saved, int to catch EOF */
int endinput = 0;               /* position of '\0' in line[] */
int idxinput = 0;               /* position of character being read by getop() */

/* getline_: get a line of input */
void getline_()
{
    if (line[idxinput] != '\0')     /* if it didn't reach end of input, don't keep asking for input */
        return;
    idxinput = 0;                   /* else, ask for input again, reset index position */
    int i = 0;
    int c;
    while ((line[i++] = c = getchar()) != EOF && c != '\n' && i<MAXINPUT-1)
        ;
   
    line[i] = '\0';
    endinput = i;
}


#include <ctype.h>

/* getop: get next character or numeric operand */
int getop(char s[])
{
    getline_();
    int i = 0;          /* index for s[] */
    int j = idxinput;   /* index for line[] */
    int c;              /* current char */    

    while ((s[0] = c = line[j++]) == ' ' || c == '\t')  /* skip white space */
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.') {
        idxinput = j;
        return c;                   /* not a number */
    }

    if (isdigit(c))                 /* collect integer part */
        while (isdigit(s[++i] = c = line[j++]))
            ;
    if (c == '.')                   /* collect fraction part */ 
        while (isdigit(s[++i] = c = line[j++]))
            ;
    s[i] = '\0';
    idxinput = j;
    return NUMBER;
} 