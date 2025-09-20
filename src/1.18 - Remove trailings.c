/* Write a program to remove trailing blanks and
tabs from each line of input, and to delete entirely
blank lines. */

#include <stdio.h>
#define LENGTH 200

int in(char chr, char arr[], int len);
int getinput(char arr[], int lim);

void allzeros(char arr[], int len);
void remove_trailing(char arr[], int len);



int main()
{
    char string[LENGTH];
    char c;
    int i;
    
    allzeros(string, LENGTH);
    while(getinput(string, LENGTH) > 1);  
}

// Gets user input, stops when:
// 1. Newline; 2. EOF; 3. Length of input > limit
int getinput(char arr[], int lim)
{
    int i;
    int j;
    char c;

    for (i=0; (c=getchar()) != EOF && c != '\n' && i < lim; ++i)
    {
        arr[i] = c;
    }
    remove_trailing(arr, i);
    for (j=0; j < i; ++j)
    {
        printf("%c", arr[j]);
    }
    printf("\n");
    return i;
}

// Check if a character is in a string.
int in(char chr, char arr[], int len)
{
    // chr = character to look for
    // arr = in this array
    // len = lenght of the array

    for (int i=0; i<len; ++i)
    {
        if (arr[i] == chr)
        {
            return 1;
        }
    }
    return 0;
}

// Set all items from an array to zero
void allzeros(char arr[], int len)
{
    int i;
    for (i=0; i<len; ++i)
    {
        arr[i] = '\0';
    }
}

// Removes trailing (blank characters at the end of a line)
void remove_trailing(char arr[], int len)
{
    char blank_space[] = "\t\n ";    // <- Len = 3
    int len_bs = sizeof(blank_space) / sizeof(blank_space[0]);
    int i;

    for (i=len; i > -1; --i)
    {
        if (in(arr[i], blank_space, len_bs))
        {
            arr[i] = '\0';
        }
        else
        {
            break;
        }
    }
}