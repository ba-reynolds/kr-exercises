#include <stdio.h>

#define START_UPPER 65      // ASCII start for the uppercase alphabet
#define START_LOWER 97      // ASCII start for the lowercase alphabet
#define START_VALUE 10      // Lowest value a letter can hold in hexadecimal (A|a = 10)
#define HEX_STEP    16      // Each digit|letter is 16 times bigger than the previous one

int htoi(char s[], int len);

int main()
{
    char string[] = "0x3179831A";
    int len_str = sizeof(string) / sizeof(string[0]) + EOF;

    printf("%d", htoi(string, len_str)); 
    return 0;
}

int htoi(char s[], int len)
{
    int i;
    int mult = 1;       // Multiplier, starts at 1 because it starts from the end
    int rslt = 0;       // Result to return
    
    const int INDEX_LAST_ITEM = len-1;

    
    for (i=INDEX_LAST_ITEM; i > -1; --i){                 // Iterating in reverse

        if (s[i] == 'x' || s[i] == 'X'){        // In case the string starts with 0x...
            break;
        }

        if (s[i] >= '0' && s[i] <= '9'){        // A digit?
            rslt += (s[i] - '0') * mult;
        }

        if (s[i] >= 'A' && s[i] <= 'F'){        // An uppercase letter?
            rslt += (s[i] - (START_UPPER - START_VALUE)) * mult;            
        }

        if (s[i] >= 'a' && s[i] <= 'f'){        // A lowercase letter?
            rslt += (s[i] - (START_LOWER - START_VALUE)) * mult;
        }

        mult *= HEX_STEP;                       // Increment multiplier
    }
    return rslt;
}