#include <stdio.h>

#define ARR_SIZE    100
void reverse(char arr[]);

/* Exercise 3-4. In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs. */

/* The reason it can't represent the "biggest" negative number as positive is because, in a twos
complement, there's always one more negative number than positive. */

void itoa(unsigned n, char s[])
{
    int sign;
    if ((sign = n) < 0)
        n = -n;

    int i = 0;
    do {
        s[i++] = n % 10 + '0';
        n /= 10;
    } while (n>0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* Reverses a character array AKA string */
void reverse(char arr[])
{
    int i;      /* Index array */
    int temp;   /* Variable used to swap values */

    for (i=0; arr[i] != '\0'; ++i)  /* Find EOF */
        ;
    /* You wanna leave the EOF as it is, that's why you substract 1*/
    int j = i-1;
    
    for (i=0; i<j; ++i, --j){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    } 
}

int main()
{
    int n = -2147483648;
    char arr[ARR_SIZE];
    char idkk[] = "BUENOS DIAS 123 TEST";
    itoa(n, arr);
    printf("%s", arr);

}