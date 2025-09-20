#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define ALLOCSIZE 100000
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

/* alloc: hand out (unused) blocks of memory from allocbuf */
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp-n;
	}
	printf("alloc: not enough space in allocbuf\n");
	return NULL;
}

/* write from -> to */
void write(char *, char *);

/* allocline: allocates lines of input to allocbuf */
int allocline(char line[], int linelen, char *lineptr[])
{
	char *startbuf;
	if ((startbuf = alloc(linelen)) != NULL) {
		write(line, startbuf);
		*lineptr = startbuf;
		return 0;
	}
	/* because (MAXLINES * MAXLINELEN = ALLOCSIZE) */
	/* this should never happen, but just in case... */
	printf("allocline: error, couldn't allocate entire line in allocbuf\n");
	return 1;
}

#define MAXLINES 200 /* max amount of lines to be read */
#define MAXLINELEN 500 /* max length for each line */
char *lineptr[MAXLINES];

/* readline: reads a line of input, return length of line */
int readline(char line[], int linesize)
{
	int c, i = 0;
	while (--linesize && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;	

	if (c == '\n')
		line[i++] = c;
	
	line[(i > 0) ? i++ : i] = '\0'; 
	return (linesize == 0) ? -1: i;
	/* whether the entire line could fit into the array */
}

/* write: writes the content of *s to *t */
void write(char *s, char *t)
{
	while (*t++ = *s++)
		;
}

/* swap: swaps two elements */
void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


/* qsort: sort an array using the quick sort algorithm */
/* receives a pointer to a function to determine the kind of sort */
void qsort_(void *v[], int left, int right,
int (*comp)(void *, void *))
{
	if (left >= right)
		return;

	int i = left + 1;
	int last;
	for (last = left; i <= right; i++)
		if (comp(v[i], v[left]) < 0)
			swap(v, i, ++last);
	
	swap(v, last, left);
	qsort_(v, left, last-1, comp);
	qsort_(v, last+1, right, comp);	
}

/* numcmp: returns difference between float s1 and s2 */
int numcmp(void *s1, void *s2)
{
	float v1 = atof(s1);
	float v2 = atof(s2);
	return v1-v2;
}

/* strcmp_: compares two strings, returns diff between s1 & s2 */
int strcmp_(void *s1, void *s2)
{
	char *c1 = (char *)s1;
	char *c2 = (char *)s2;

	for (; *c1 == *c2; c1++, c2++)
		if (*c1 == '\0')
			return 0;
	return *c1-*c2;
}

/* fold: case distinctions are not made during sorting; 
for example, a and A compare equal */
int fold(void *s1, void *s2)
{
	char *c1 = (char *)s1;
	char *c2 = (char *)s2;

	for (; tolower(*c1) == tolower(*c2); c1++, c2++)
		if (*c1 == '\0')
			return 0;
	return tolower(*c1) - tolower(*c2);
}

/* rev_arr: reverses an array */
void rev_arr(void *arr[], int size)
{
	int i = 0;
	while (i < --size)
		swap(arr, i++, size);
}

#define NUMERIC 1	/* 0001 */
#define REVERSE 2	/* 0010 */
#define FOLD	4	/* 0100 */

/* get_flags: gets cmd arguments like -n, -r */
int get_flags(int argc, char *argv[])
{
	char c;
	int flags = 0;

	while (--argc && **++argv == '-')
		while (c = *++*argv)
			switch (c) {
			case 'n':
				flags |= NUMERIC;
				break;
			case 'r':
				flags |= REVERSE;
				break;
			case 'f':
				flags |= FOLD;
				break;			
			default:
				return -1;
			}
	return flags;
}

int handle_errors(int len, int nlines, int maxlines, int maxlinelen, int flags)
{	
	if (len == -1) {
		printf("handle_errors: error, length of line %d >= %d\n", nlines+1, maxlinelen);
		return 1;
	}
	if (nlines > maxlines) {
		printf("handle_errors: error, can't hold any more lines\n");
		return 1;
	}
	if (flags < 0) {
		printf("handle_errors: error, use one of the following flags [-n, -r]");
		return 1;
	}
	return 0;
}


int main(int argc, char *argv[])
{
	char line[MAXLINELEN];
	int len; 		/* length of input line */
	int nlines = 0;	/* #lines that have been read */	

	while ((len = readline(line, MAXLINELEN)) > 0 && nlines <= MAXLINES)
		if (allocline(line, len, &lineptr[nlines++]) == 1) 
			break;
	
	int flags = get_flags(argc, argv); /* cmd arguments (ie: -n, -r) */
	if (handle_errors(len, nlines, MAXLINES, MAXLINELEN, flags))
		return 1;

	qsort_((void**)lineptr, 0, nlines-1, (flags & NUMERIC) ? numcmp : (flags & FOLD) ? fold : strcmp_);

	if (flags & REVERSE)
		rev_arr((void**)lineptr, nlines);

	for (int i = 0; i < nlines; i++)
		printf("%s", lineptr[i]);
}