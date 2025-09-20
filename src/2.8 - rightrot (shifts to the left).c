#include <stdio.h>

// Really proud of this one.

/* Exercise 2-8. Write a function rightrot(x,n)
-* that returns the value of the integer x rotated
-* to the right by n positions. */

int signficant_bit(unsigned n)
{
    int x = 1;
    while ((n >>= 1) & ~0)
        x <<= 1;

    return x;
}

int right_rot(unsigned n, int k)
{
    int s_bit = signficant_bit(n);
    
    while (k-- != 0){
        /* If the last bit is a one, then n = n rotated to the right
        -* plus the most significant bit (it shifts back to the left), 
        -* else (last bit not a one) just n rotated to the right */
        n = (n&1) ? (n>>1)+s_bit: n>>1;
    }
    return n;
}

int main()
{
    int x = 9;
    int i = 0;
    while (i++ != 20)

        printf("%5d %5d\n", right_rot(128, i), i);

}