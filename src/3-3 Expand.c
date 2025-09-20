#include <stdio.h>

/* Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally. */

/* Se asume que el usuario sabe lo que hace y no pone cosas como "1-]" o "A-1"*/
/* Esto es facil de verificar, pero es paja poner 8e+10 if statements */

/* Metodologia de la investigacion */


/* Algunos valores estan de decoracion XD */
#define START_DIGITS    48
#define END_DIGITS      57

#define START_UPPPER    65
#define END_UPPER       90

#define START_LOWER     97
#define END_LOWER       122

#define ARR_LEN         100

void expand(char s1[], char s2[])
{
    /* If the string starts with a dash then the dash is taken literally */
    int i = (s1[0] == '-') ? 1: 0;  /* Index string 1 */
    int j;                          /* Index 'for' loop */
    int k = 0;                      /* Index string 2 */
    if (i != 0)                     /* If the starting char was a dash */
        s2[k++] = '-';

    int start, end, mult;

    while (s1[i] != '\0'){
        start   = s1[i];
        end     = s1[i+2];
        mult    = (start < end) ? 1: -1;        /* In case the ASCII value of start > end (E.g a-Z) */
        end     += mult;                        /* Includes the last char, otherwise a-z = abc..wxy */

        for (j=start; j != end; j += mult){
            
            if (j>END_UPPER && j<START_LOWER)   /* Ignore chars between upper and lower alphabet */
                continue;
            s2[k++] = j;
        }

        i += 2;    
        if (s1[i+1] != '-')                     /* It either reached EOF or a situation like: a-z0-9 */
            i += 1;
    }

    s2[k] = '\0';                               /* Marking the EOF on string 2 */
}



int main()
{
    char str[] = "-A-z0-1-4O-Q";
    char exp[ARR_LEN];
    expand(str, exp);
    printf("%s\n", exp);
    return 0;
}