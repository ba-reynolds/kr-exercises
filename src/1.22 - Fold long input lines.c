#include <stdio.h>
#define MAXLENINPUT 100
#define COLUMNBREAK 15
#define TABBREAK 8


/*
Write a program to "fold" long input lines into two or more
shorter lines after the last non-blank character that occurs before the n-th
column of input. Make sure your program does something intelligent with very
long lines, and if there are no blanks or tabs before the specified column.
*/

char    line[MAXLENINPUT];

// ༼ つ ◕_◕ ༽つ Congrats :)) !
/*
What was your main problem?
You tried to do everything at the same time.
Split the task into manageable tasks, and take your
Time with each of them. Don't try to do everything at once */

/* Think of multiple ways to implement something, then
choose the one you see fit */

int     input();
int     detab(int indx);
int     lenword(int indx, int len);
void    splitlines(int len);
void    printl(int len);
void    istab(int len);

int main()
{
    int i;
    int strlen;

    while ((strlen=input(MAXLENINPUT)) > 0)
    {
        splitlines(strlen);
    }
}

int input()
{
    int i;
    int add;
    char c;

    for (i=0; (c=getchar()) != EOF && c != '\n'; ++i)
    {
        line[i] = c;

        if (c == '\t')
        {            
            add = detab(i);
            i += add;
            // The reason I'm doing this is because the next iteration
            // Of the for loop 'i' will get added 1, which fucks up the tab breaks
            // And it means that the next time c == \t, it won't add the right
            // Amount of spaces.
            i -= 1;
        }
    }
    // Length of the string
    return i;
}

// Replaces tab characters by the right amount of spaces until
// The next tab break
int detab(int indx)
{
    int i;
    int amt_spaces = TABBREAK;

    for (i=0; i<indx; ++i)
    {
        // --- Doing something similar to module --- //
        --amt_spaces;
        if (amt_spaces == 0)
            {amt_spaces = TABBREAK;}
        // ----------------------------------------- //
    }

    for (i=0; i < amt_spaces; ++i)
    {
        line[indx+i] = ' ';
    }
    return amt_spaces;

}


void splitlines(int len)
{
    int i;
    // Length of the first word
    int len_word = lenword(i, len);
    int len_line = 0;
    for (i=0; i<len; ++i)
    {
        
        // Removing blank spaces from the start of the line
        for (; len_line == 0 && line[i] == ' '; ++i);

        ++len_line;

        if (line[i] == ' ')
        {
            // Updating the length to match the length of the current word
            len_word = lenword(i, len);
            if (len_line + len_word >= COLUMNBREAK)
                {
                    printf("\n");
                    len_line = 0;                    
                
                }else{
                    putchar(line[i]);
                }
        }
        else
            {putchar(line[i]);} 

        // This condition will only trigger if the length of the
        // Current word is greater than COLUMNBREAK
        if (len_line >= COLUMNBREAK)
        {
            putchar('\n');
            len_line = 0;
        }

    }
    putchar('\n');
}

// Returns length of the current word
int lenword(int indx, int len)
{
    int i;
    int j;

    // Making sure I don't start from a blank character
    for (i=indx; line[i] == ' '; ++i);

    // Getting the length of the word
    for (j=i; line[j] != ' ' && j<len; ++j);

    return j-i;
}

void printl(int len)
{
    int i;
    for (i=0; i<len; ++i)
    {
        printf("%c", line[i]);
    }
    printf("\n");
}

void istab(int len)
{
    int i;
    for (i=0; i<len; ++i)
    {
        printf("%i", (line[i] == '\t'));
    }
    printf("\n");    
}