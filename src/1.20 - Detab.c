#include <stdio.h>

#define TABSTOP 8

void detab(char arr[], int len);
void multchr(char chr, int n);

int main()
{
    char string[] = "bautista\tbautist\tbautis\tbauti";
    int sizestr = sizeof(string) / sizeof(string[0]);
    detab(string, sizestr);

}

// Replaces tabs for spaces until the next tab stop
void detab(char arr[], int len)
{
    int i;
    int amt_space = TABSTOP;

    for (i=0; i < len; ++i)
    {
        
        if (arr[i] == '\t')
        {
            multchr(' ', amt_space);
            amt_space = TABSTOP+1;
            // Reseting amt_space to its initial value because
            // It already reached a tab stop.
            // Adding 1 to TABSTOP because amt_space will decrease
            // By 1 a few lines below.
        }
        else
        {           
            printf("%c", arr[i]);
        }

        amt_space = (amt_space-1);
        if (amt_space == 0)
        {
            amt_space = TABSTOP;
        }        

    }
}

// Print a character n amount of times
void multchr(char chr, int n)
{
    int i;
    for (i=0; i < n; ++i)
    {
        printf("%c", chr);
    }
}