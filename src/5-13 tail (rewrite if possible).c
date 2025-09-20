/* 3. Write the program tail, which prints the last n lines of its input.
-* By default, n is set to 10 */

/* lines should be stored as in the sorting program of Section 5.6, 
-* not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>

#define ALLOCSIZE 10000
char buf[ALLOCSIZE];
char *bufp = buf;

/* alloc: returns a pointer to the next avaible block in buf */
char *alloc(int n)
{
	if (buf + ALLOCSIZE - bufp >= n) {
		bufp += n;
		return bufp-n;
	}
	printf("alloc: error, not enough space\n");
	return NULL;
}

/* getline_: gets a line of input */
int getline_(char line[], int arrsize)
{
	int c, i = 0;
	while (i < arrsize-1 && (c = getchar()) != '\n' && c != EOF)
		line[i++] = c;
	line[i++] = '\0';

	return (c == EOF && i == 1) ? EOF: i;
}

/* write: writes the contents of s to *p, including '\0' */
void write(char *s, char *p)
{
	while (*p++ = *s++)
		;	
}

#define LENLINE 1000 /* maximum length for a line */
#define MAXLINES 100 /* maximum amount of lines */
#define DEAULTPRINT 10 /* default #lines to be printed */
char *pointers[MAXLINES]; /* points to the start of each line saved in buf */


int main(int argc, char *argv[])
{
	char line[LENLINE];		/* where each line of input gets stored */
	int linelen; 			/* length of the current line */
	int nlines = 0; 		/* current #lines received from input */
	int l2p = -1; 			/* #lines to be printed */
	char *startbuf; 		/* pointer to the start of the memory allocated alloc() */


	while (--argc)
		if (**++argv == '-')
			l2p = atoi(++*argv);
	l2p = (l2p == -1) ? DEAULTPRINT: l2p;


	while ((linelen = getline_(line, LENLINE)) != EOF && nlines < MAXLINES) {
		
		if ((startbuf = alloc(linelen)) != NULL) {
			write(line, startbuf);
			pointers[nlines++] = startbuf;
		}
		else
			return -1;
	}

	int i = (nlines-l2p < 0) ? 0: nlines-l2p;
	while (i < nlines)
		printf("%s\n", pointers[i++]);

}