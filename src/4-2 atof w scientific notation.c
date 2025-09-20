#include <stdio.h>

double pow_(int n, int k)
{
    int i;
    double result = 1;
    if (k>0)
        for (i=0; i<k; ++i, result*=n)
            ;
    else
        for (i=0; i<-k; ++i, result/=n)
            ;
    return result;
}

double atof(char arr[])
{
    int i = 0;                                          /* Array index */
    int sign = 1;                                       /* Positive or negative */
    double pwr = 1;                                     /* For decimal part, double to avoid int div */
    double result = 0;

    if (arr[i] == '-')
        sign = -1;

    if (arr[i] == '-' || arr[i] == '+')                 /* Skip sign */
        ++i;

    while (arr[i] != '.' && arr[i] != '\0'){            /* Integer part */
        if (arr[i] == 'e' || arr[i] == 'E')
            goto sci_notation; 
        result = result * 10 + (arr[i++] - '0');
    }

    if (arr[i] == '.')                                  /* Skip decimal dot */
        ++i;    

    while (arr[i] != '\0'){
        if (arr[i] == 'e' || arr[i] == 'E')
            goto sci_notation; 
        result += (arr[i++] - '0') / (pwr*=10);
    }
    return sign * result;

    sci_notation: ;

        int exponent = 0;
        int sign_exp = 1;
        ++i;                                    /* Skip 'e'|'E' */
        if (arr[i] == '+' || arr[i] == '-'){    /* Check for sign */
            if (arr[i] == '-')
                sign_exp = -1;
            ++i;                                /* Skip sign */
        }                                       /* Otherwise assume exponent is positive */
        
        while (arr[i] != '\0')                  /* Get exponent */
            exponent = exponent * 10 + (arr[i++] - '0');
        
        exponent *= sign_exp;
        return sign * (result * pow_(10, exponent));  
}



int main()
{
    // char arr[] = "-1.23e-2";
    char arr[100];
    gets(arr);

    double x = atof(arr);
    printf("%s\n\n", arr);
    printf("Result: %lf\n", x);
}