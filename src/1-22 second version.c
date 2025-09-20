#include <stdio.h>

#define TABBREAK 	8		/* how many spaces represent a tab */
#define LINEBREAK 	16		/* max amount of characters per line */
#define MAXINPUT 	100		/* max amount of input (characters) at once */


/* untab: replaces tab with spaces, respects tab breaks */
/* returns new array index after adding spaces */
int untab(char s[], int index)
{
	int i;
	int amt;				/* amount of spaces to replace tab */

	amt = TABBREAK - (index % TABBREAK);

	if (amt == 0)
		amt = TABBREAK;		/* reached a tab break, starts again */

	i = index;
	while (i < index+amt)
		s[i++] = ' ';

	return i;
}


/* getline_: input until it meets a new line character. saves input in s */
/* returns the length of the input */
int getline_(char s[], int limit)
{
	int c;
	int i = 0;
	while ((s[i++] = c = getchar()) != EOF && c != '\n' && i < limit-1)
		if (c == '\t')
			i = untab(s, i-1);

	if (i >= limit)
		s[limit-1] = '\0';
	else
		s[i] = '\0';
	
	return i-1;
}

/* nextblank: ... */
/* returns the index of the next blank space that comes after a word */
/* E.g "kit   foo " <- you would call this function after 't' */
/* and it would return index + 6 characters before the space after "foo" */
int nextblank(char s[], int index)
{
	int i = index;		/* used 'i' because it looks cleaner than index */

	while (s[i] == ' ' && s[i++] != '\0')	/* skip space before the word */
		;
	while (s[i] != ' ' && s[i++] != '\0')	/* find first space after word */
		;
	/* i-1 because you want the index of the character previous to the space */
	return i-1;
}

/* fold: folds long input lines into two or more shorter lines after
the last non-blank character that occurs before the n-th column of input. */
void fold(char s[])
{
	int i;				/* index for array */
	int ll;				/* length of the current line */
	int nb;				/* index of next blank after a word */
	
	for (i=ll=nb=0; s[i] != '\0'; ++i) {
		
		++ll;

		while (s[i] == ' ' && ll == 1) /* skip initial blankspace from a line */
			++i;

		if (s[i] == ' ')
			nb = nextblank(s, i);

		if (ll + (nb-i) < LINEBREAK)	/* if next word fits in line */
			putchar(s[i]);
		else {							/* else reset the line */
			ll = 0;
			putchar('\n');			
		}

		if (ll >= LINEBREAK) {			/* in case a word is > LINEBREAK */
			ll = 0;
			putchar('\n');
		}
		
	}

}

int main()
{
	char line[MAXINPUT];
	int len;
	while ((len=getline_(line, MAXINPUT)) > 0) {
		fold(line);
	}
	return 0;
}