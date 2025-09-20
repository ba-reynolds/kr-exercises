#include <stdio.h>

/* Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. */

int main(){

    int c, k;

    c = getchar();
    k = -1;

    for (; c != EOF; c = getchar()){
        
        if (!(k == ' ' && c == ' ')){
            printf("%c", c);
        }
        k = c;

    }

}