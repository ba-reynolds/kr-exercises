#include <stdio.h>

#define IN 1        /* 'Inside' a word */
#define OUT 0       /* 'Outside' a word */

/* Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. */

int main(){

    int c, len_word, index, arr_words[100], state;      /* input, keep track length of a word, index for the array, array to store the length of the words, inside or outside a word */
    int i, j;       /* Variables for 'for' loops */

    len_word = 0;
    index = -1;     /* -1 Because it will go one up when it enters the loop for the first time */
    state = OUT;    /* Inside or outside a word, OUT by default */

    for (i = 0; i < 99; ++i){
        arr_words[i] = 0;       /* Changing the value of all the items in the array to 0 */
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

    int max_len_word, len_current_word;
    max_len_word = 0;


    for (i = 0; i < index+1; ++i){ /* Iterating through the aray and getting the maximum length of a word in the array */
        len_current_word = arr_words[i];
        if (len_current_word > max_len_word){
            max_len_word = len_current_word;
        }
    }


    for (i = 0; i < index+1; ++i){

        for (j = 0; j < index+1; ++j){


            len_current_word = arr_words[j];
            if (len_current_word != max_len_word){
                printf(" ");                
            }
            else{
                printf("|");
                --arr_words[j];
            }
                         
        }
        printf("\n");
        --max_len_word;
        if (max_len_word == 0){
            break;
        }        
    }

}