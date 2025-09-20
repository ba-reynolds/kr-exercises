#include <stdio.h>

/* Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged. */

/* To help you visualize:
-* https://stackoverflow.com/questions/15698619/what-function-is-kr-exercise-2-6-really-asking-for */


// Print binary representation of a number, doesn't work for negative nums
void print_bin(int n)
{
    char store_in[64];
    int i = 0;

    while (n != 0){
        store_in[i] = (n&1 == 1) ? '1': '0';
        ++i;
        n >>= 1;
    }
    --i;
    while (i>-1){
        putchar(store_in[i]);
        printf("%c", (i%4 == 0) ? ' ': '\0');
        --i;
    }
    printf("\n");
}


/* Returns the value of the biggest (turned on) bit from an unsigned int */
/* 3 -> 11 = 2; 9 -> 1100 = 8 */
int biggest_bit(unsigned int n)
{
    int result = 1;
    while ((result<<=1) < n);

    if (result != n)
        return result>>1;
    
    return result;
}

// Mas corto que la anterior, mas mejor!
int signficant_bit(unsigned n)
{
    int x = 1;
    while ((n >>= 1) & ~0)
        x <<= 1;

    return x;
}

/* Returns the first (k) bits from (n), starting from the right */
/* n = 10011010, k = 4; result -> 1010 */
int first_bits(unsigned int n, int k)
{
    int result = 0;     // Value to return
    int i      = 0;     // Value to iterate over
    int mask   = 1;     // Value to perform and opeartion with, gets left shifted k amount of times

    while (i<k){
        result += (n & mask);
        mask <<= 1;
        ++i;
    }

    return result;
}

/* first_bits optimizado */
int first_bits_opt(int n, int k)
{
    // ~0           = 1111...1111
    // ~0 << k      = 1111...1000
    // ~(~0 << k)   = 0000...0111
    // n & _        = first bits
    return n & ~(~0 << k);
}

int setbits(int x, int p, int n, int y)
{
    int first_bits_y = first_bits_opt(y, n);
    // 0=0000 -> ~0=1111 -> ~0<<n=1100 -> ~(~0<<n)=0011
    int mask = ~(~0 << n);
    return (first_bits_y << p) | (~(mask << p) & x);
}

int main()
{
    int x = 58050;
    int y = 19825;
    int p = 6;
    int n = 5;
    int a = setbits(x, p, n, y);

    printf("%d", a);
    printf("\n");
    print_bin(a);
    
}