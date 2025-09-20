#include <stdio.h>
#define SIZE_ARR 26

/* Write a program to print a histogram of the frequencies of different characters in its input. */

int main(void) {
    int arr[SIZE_ARR], c;
    int i;

    for (i = 0; i < SIZE_ARR; ++i){
        arr[i] = 0;
    }

    while ((c = getchar()) != EOF){
        if (c >= 'A' && c <= 'Z'){
            ++arr[c-'A'];
        }
    }
    printf("\n");

    int max_item, current_item;
    max_item = current_item = 0;

    for (i = 0; i < SIZE_ARR; ++i){
        current_item = arr[i];
        if (current_item > max_item){
            max_item = current_item;
        }
    }

    while (max_item > 1){
        for (i = 0; i < SIZE_ARR; ++i){
            current_item = arr[i];
            if (current_item == max_item){
                printf("|");
                --arr[i];
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        --max_item;
    }

    for (i = 0; i < SIZE_ARR; ++i){
        printf("%c", 'A'+i);
    }


}