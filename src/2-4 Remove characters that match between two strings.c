/* Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2. */

#include <stdio.h>

enum {FALSE, TRUE};

void squeeze(char str1[], char str2[])
{
    
    int ind_1, ind_2;       // Index for str1, str2
    int ind_n;              // Index for the new string

    int found_match = FALSE;

    for (ind_1=0; str1[ind_1] != '\0'; ++ind_1){        // Iterate over first str

        for (ind_2=0; str2[ind_2] != '\0'; ++ind_2){    // Iterate over scnd str

            if (str1[ind_1] == str2[ind_2]){            // If there's a match
                found_match = TRUE;} 
        }

        if (found_match != TRUE){           // If there wasn't a match
            str1[ind_n++] = str1[ind_1];}   // Then update the new string

        found_match = FALSE;                // Reset value every loop

    }
    str1[ind_n] = '\0';                     // Mark the end of the string
    
}

void printarr(char arr[])
{
    for (int i=0; arr[i] != '\0'; ++i){
        putchar(arr[i]);
    }
    putchar('\n');
}

int main()
{
    char idk[] = "TEHEEDEHEEHSHEHE";
    char kdi[] = "EDH";
    printarr(idk);
    squeeze(idk, kdi);
    printarr(idk);
}