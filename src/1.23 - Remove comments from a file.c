#include <stdio.h>

/* Write a program to remove all comments from a C program.
Don't forget to handle quoted strings and character constants properly. 
C comments do not nest */


#define OPEN_COMM       '/'     // Initial character to open a comment
#define SECOND_SING     '/'     // Secondary character to open a single line comment
#define SECOND_MULT     '*'     // Secondary character to open a multi line comment
#define BACKSLASH       '\\'    // For escape sequences

#define TRUE            1
#define FALSE           0

int in_sing_comm    = FALSE;    // In a single line comment "//"
int in_mult_comm    = FALSE;    // In a multi  line comment "/*"
int in_string       = FALSE;    // In a string '"..."'
int in_char_const   = FALSE;    // In a character constant "'.'"
int in_esc_seq      = FALSE;   // If inside a escape sequence (E.g '\\')

char last_char = '\0';          // Stores the value of the previous character

/* Note: "cc" stands for "Current Character" */
int     notin(void);
void    inchr(char cc);
void    incomm(char cc);


int main()
{
    char c;
    
    while ((c=getchar()) != EOF){
        inchr(c);
        incomm(c);
        // Comment output gets handled in incomm()
        last_char = c;
    } 
    printf("\n");
  
    return 0;
}


/* Checks if not currently in:
    1. A comment (of any kind)
    2. A string
    3. A character constant */
int notin(void)
{
	if (!in_sing_comm && !in_mult_comm && !in_string && !in_char_const)
        return TRUE;
    return FALSE;
}


/* Checks if the program enters a:
    1. String
    2. Character constant
Comment checking is done in the function below */
void inchr(char cc)
{
    if (cc == '"' && notin()){                                              // Enter string
        in_string = TRUE;
    }
    else if (cc == '"' && in_string == TRUE && in_esc_seq == FALSE){        // Exit string
        in_string = FALSE;
    }

    if (cc == '\'' && notin()){                                             // Enter character constant
        in_char_const = TRUE;
    }
    else if (cc == '\'' && in_char_const == TRUE && in_esc_seq == FALSE){   // Exit character constant
        in_char_const = FALSE;
    }

    /* Handle espace sequences to avoid early exits in situations like: "\""
    This works for all kinds of escape sequences, including '\\' */

    if (cc == BACKSLASH && (in_string || in_char_const) == TRUE && in_esc_seq == FALSE){
        in_esc_seq = TRUE;
    }
    else if (last_char == BACKSLASH && (in_string || in_char_const) == TRUE && in_esc_seq == TRUE){
        in_esc_seq = FALSE;
    }
    // -------------------------------------------------------------------- //

}

/* Checks if the program is inside a comment */
void incomm(char cc){


    if (notin() && last_char == OPEN_COMM){     // Possible comment opening
        if (cc == SECOND_SING ){                // In single line comment?           
            in_sing_comm = TRUE;
        }
        else if (cc == SECOND_MULT){            // In multi line comment?            
            in_mult_comm = TRUE;
        }
    }
    else if (in_sing_comm){                     // If already in a single line comment
        if (cc == '\n'){                        // Then the comment ends when it reaches a new line            
            in_sing_comm = FALSE;
        }
    }
    else if (in_mult_comm){                     // If already in a multi line comment
        if (last_char == '*' && cc == '/'){     // Then the comment ends when it reaches "*/"            
            in_mult_comm = FALSE;
        }
    }
    else{
        /* The reason I don't print the current character is because 
        it may be the opening for a comment ("/") */
        putchar(last_char);
    }
}

