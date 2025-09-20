#include <stdio.h>

#define TRUE    1
#define FALSE   0
#define BACKSLASH '\\'

char    last_char = '\0';
int     in_str = FALSE;
int     in_esc_seq = FALSE;     // In a escape sequence (backslash)

void multchar(char chr, int n);
void instr(char cc);

int main()
{
  
    char c;

    
    multchar('-', 30);
    
    while ((c=getchar()) != EOF){
        // putchar(c);
        instr(c);
        if (c == '\n'){
            putchar(c);
        }else{
            printf("%i", in_str);
        }
        last_char = c;
    }  
    
    putchar('\n');
    multchar('-', 30);   
  
    return 0;
}

/* Print chr n amount of times */
void multchar(char chr, int n)
{
    int i;
    for (i=0; i < n; ++i)
    {
        putchar(chr);
    }
    putchar('\n');
}

void instr(char cc)
{
    if (cc == '"' && in_str == FALSE){
        in_str = TRUE;
    }
    else if (cc == '"' && in_str == TRUE && in_esc_seq == FALSE){
        in_str = FALSE;
    }

    if (cc == BACKSLASH && in_str == TRUE && in_esc_seq == FALSE){
        in_esc_seq = TRUE;
    }

    else if (last_char == BACKSLASH && in_str == TRUE && in_esc_seq == TRUE){
        in_esc_seq = FALSE;
    }

}