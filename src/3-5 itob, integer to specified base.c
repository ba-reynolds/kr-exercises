#include <stdio.h>

/* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s. */


/* Reverse a character array (or string as the cool kids call 'em) */
void reverse(char s[])
{
    int i;
    for (i=0; s[i] != '\0'; ++i) /* Search EOF */
        ;
    int j = i-1;                /* -1 Because s[i] = EOF, and you don't wanna touch the EOF */
    int temp;                   /* Temporary variable for the swap */
    for (i=0; i<j; ++i, --j){
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

/* Number, array to save on, base(d) */
void itob(unsigned n, char s[], int b)
{
    int i = 0;
    int sign;
    if ((sign=n) < 0)
        n = -n;
    char chr;   /* Character that will represent that base */
    do
    {
        /* In ASCII, the upper case alphabet doesn't come after '9',
        So you have to make sure that if the number is greater than 9
        (Greatest digit in decimal) then it starts with the alphabet */
        chr = n % b;    
                        
        s[i++] = (chr>9) ? chr%10 + 'A': chr + '0';

    } while ((n/=b) > 0);

    if (sign<0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    int x = 10;
    int base = 11;
    char arr[10];

    itob(x, arr, base);
    printf("%s", arr);
}