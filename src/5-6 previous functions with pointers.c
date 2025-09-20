#include <stdio.h>
#define SIZE 100

int getline_(char *s)
{
	char *cs = s;
	while ((*s = getchar()) != '\n' && *s != EOF)
		s++;
	*s = '\0';
	return s-cs;
}

int abs(int n)
{
	return (n < 0) ? -n: n;
}

/* itoa: turns an integer to an array of characters */
void itoa(char *arr, int n)
{
	static char *p = NULL;
	if (n < 10 && n > -10) { /* reached maximum level recursion */
		p = arr;
		if (n < 0)
			*p++ = '-';
	}	
	if (n/10)
		itoa(arr, n/10);
	
	*p++ = abs(n)%10 + '0';
	*p = '\0';
}

#define SWAP(t, x, y) {t tmp = x; x = y; y = tmp;}

/* reverse: reverse a string */
void reverse(char *s)
{
	char *end = s;
	while (*end)
		end++;
	for (end--; s < end; s++, end--) {
		SWAP(char, *s, *end);
	}	
}

/* strindex: returns pointer to the string s where the string
t begins, or NULL if s does not contain t. */
char *strindex(char *s, char *t)
{
	int i;
	while (*s) {
		for (i = 0; *(s+i) == *(t+i); i++)
			;
		if (*(t+i) == '\0')
			return s;
		s++;
	}
	return NULL;
}

int main()
{
	// char line[SIZE];
	// while (getline_(line) > 0)
	// 	printf("%s\n", line);


	// char arr[SIZE];
	// int x = -3123412;
	// itoa(arr, x);
	// printf("%s\n", arr);

	// x = -983127891;
	// itoa(arr, x);
	// printf("%s\n", arr);


	// char str[SIZE] = "Buenos dias 123 test!";
	// printf("%s%c", str, '\n');
	// reverse(str);
	// printf("%s%c", str, '\n');


	char str[SIZE] = "Buenos dias 123 test";
	char *p = "dias";
	char *x = strindex(str, p);
	printf(x);

}
