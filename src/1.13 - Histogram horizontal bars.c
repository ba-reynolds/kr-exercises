#include <stdio.h>

#define IN 1        /* 'Inside' a word */
#define OUT 0       /* 'Outside' a word */

/* Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. */

int main(){

    int c, len_word, index, arr_words[100], state;
    int i, j;       /* Variables for 'for' loops */

    len_word = 0;
    index = -1;     /* -1 Because it will go one up when it enters the loop for the first time */
    state = OUT;    /* Inside or outside a word, OUT by default */

    for (i = 0; i < 99; ++i){
        arr_words[i] = 0;
    }

    while ((c = getchar()) != EOF){

        if (c == ' ' || c == '\t' || c == '\n'){
            state = OUT;
            len_word = 0;

        }

        else{
            if (state == OUT){
                ++index;
            }
            state = IN;
            ++len_word;
            arr_words[index] = len_word;
        }
    }

    printf("\n");

    for (i = 0; i < index+1; ++i){ /* Iterating through the aray */
        int len_current_word = arr_words[i];
        for (j = 0; j < len_current_word; ++j){
            printf("-");
        }
        printf("\n");

    }
}