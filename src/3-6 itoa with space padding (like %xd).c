#include <stdio.h>

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

/* Integer to array */
/* Number, string to save in, amt of padded spaces */
void itob(unsigned n, char s[], int pad)
{
    int i = 0;
    int sign;
    if ((sign=n) < 0)   /* Record sign */
        n = -n;         /* Make N positive */

    do
        s[i++] = n % 10 + '0';
    while ((n/=10) > 0);

    if (sign<0)
        s[i++] = '-';

    while (i < pad)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

int main()
{
    int x = -1048575;
    int base = 16;
    char arr[32];

    itob(x, arr, 12);
    printf("%s", arr);
}