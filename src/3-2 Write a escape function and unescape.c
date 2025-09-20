#include <stdio.h>

/* converts characters like newline and tab
into visible escape sequences like \n and \t 
as it copies the string t to s */
void escape(char from[], char to[])
{

    int i;  // Index for from
    int j;  // Index for to
    i = j = 0;

    while (from[i] != '\0'){
        
        switch (from[i]){

            case '\t':                
                to[j] = '\\';
                to[++j]   = 't';
                break;

            case '\n':
                to[j] = '\\';
                to[++j]   = 'n';            
                break;

            default:
                to[j] = from[i];
                break;
        }
        ++i;
        ++j;
    }
    to[j] = '\0';
}

/* Converts escape sequences into real characters */
void unescape(char from[], char to[])
{
    int i = 0;  // Index for from
    int j = 0;  // Index for to
    
    while (from[i] != '\0'){

        if (from[i] == '\\')        // Current character is a backslash

            switch (from[i+1]){     // Analyze the next char
                case 't':           // If it equals a t
                    to[j] = '\t';   // Current char = '\t'
                    ++i;            // Skip next char (because its the 't' from '\t')
                    break;

                case 'n':           // The same but with n
                    to[j] = '\n';
                    ++i;
                    break;

                default:            // If next char is not either of those then it's just a backslash
                    to[j] = from[i];
                    break;  
            }
        else
            to[j] = from[i];
        ++i;
        ++j;
    }
    to[j] = '\0';
    
}

#define ARR_LEN 100

int main()
{
    char str[] = "Buenos dias\\t\\adasffdas\\t\\nfasdfdas\\txd";
    char to[ARR_LEN];
    char to2[ARR_LEN];
    unescape(str, to);

    printf("%s\n", to);

    escape(to, to2);

    printf("%s\n", to2);
}