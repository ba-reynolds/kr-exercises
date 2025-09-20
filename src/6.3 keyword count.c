#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define PENDING '\0'
#define SIZE sizeof keytab / sizeof *keytab

struct key {
	char *word;
	int count;
} keytab[] = {
	"_Bool", 0,
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"double", 0,
	"float", 0,
	"int", 0,
	"long", 0,
	"short", 0,
	"sizeof", 0,
	"switch", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0 
};

static int bufhold = PENDING;

int getch()
{
	if (bufhold == PENDING)
		return getchar();
	else {
		int temp = bufhold;
		bufhold = PENDING;
		return (temp);
	}
}

void ungetch(int c)
{
	bufhold = c;
}

int getword(char arr[], int lim)
{
	int c;
	char *copy = arr;

	while (isspace(*arr = c = getch()))
		;

	*++arr = '\0';
	--lim; /* -1 because you stored a char in while loop. */

	if (!isalpha(c) && c != '_') 
		return c;

	while (--lim && isalnum(c = getch()))
		*arr++ = c;

	if (!isalnum(c))
		ungetch(c);

	*arr = '\0';
	return copy[0];
}

int binsearch(struct key arr[], char *word, int size)
{
	int left = 0;
	int right = size-1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		/* if guess alphan value > alphan value of word... */
		if (strcmp(arr[mid].word, word) > 0)
			right = mid - 1;
		else if (strcmp(arr[mid].word, word) < 0)
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

void print_struct(struct key arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%10s\t%10d\n", arr[i].word, arr[i].count);
	
}


int main()
{
	char word[SIZE];
	int indx;

	while (getword(word, SIZE) != EOF)
		if (isalpha(word[0]) || word[0] == '_')
			if ((indx = binsearch(keytab, word, SIZE)) >= 0)
				keytab[indx].count += 1;
	/* todas las keywords van a ser uno port lo menos ya
	que las esta leyendo de este archivo (se mencionan en keytab) */

	print_struct(keytab, SIZE);

}