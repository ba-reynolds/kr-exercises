#include <stdio.h>

/* Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
-* position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */


// https://imgur.com/a/84rMOjb

/* x = number; p = position; n = amount */
int invert(int x, int p, int n)
{
    // Shift the target bits so they are at the start
    int bits_to_change = x >> p;
    // Composed of (n) amount of ones at the start (right)
    int mask = ~(~0 << n);
    // Negates the target bits
    int negated_bits = mask & ~bits_to_change;
    // Sets to zero all the target bits
    int zero_target = ~(mask << p) & x;
    // 'Or' operation between the int with zero as target bits
    // and the negated bits shifted below the target bits.
    printf("%d", zero_target | (negated_bits << p));
}

int main()
{
    int x = 40572;
    invert(x, 6, 3);

    return 0;
}