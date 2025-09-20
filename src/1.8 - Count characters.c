#include <stdio.h>

/* Count amount of new lines, tabs and blank
spaces from user input */

int main(){

    int c, new_line, tab, blank_space;

    blank_space = 0;
    new_line    = 0;
    tab         = 0;

    while ((c = getchar()) != EOF){
        
        if (c == ' '){
            ++blank_space;}

        if (c == '\n'){
            ++new_line;}

        if (c == '\t'){
            ++tab;}        
        
    }

    printf("Amount of blank spaces: %d\n", blank_space);
    printf("Amount of new lines: %d\n", new_line);
    printf("Amount of tabs: %d\n", tab);

}