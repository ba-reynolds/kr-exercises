#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "get_words.c"

#define DEFAULT		 6	/* default for the n of chars words must be identical in */
#define MAXWORD    100	/* max size for a word */

#define DIFFERS_GT	 1	/* word doesn't belong in the group, and w1 > w2 */
#define BELONGS		 0	/* w2 belongs in the same group as w1. w2 may be eq to w1 */
#define DIFFERS_LT	-1	/* word doesn't belong in the group, and w1 < w2 */


/* comp: checks if two words are identical in their first 'n' chars */
int comp(char *w1, char *w2, int n)
{
	int cond = strcmp(w1, w2);

	while (*w1++ == *w2++ && --n > 0)
		;

	if (n == 0 || cond == 0)
		return BELONGS;

	else if (cond > 0)
		return DIFFERS_GT;
		
	else
		return DIFFERS_LT;
}


/* binary tree, where each node points to the start of a linked list */
struct node {
	struct node *lnode;			/* left child */
	struct node *rnode;			/* right child */
	struct element *start_ll;	/* pointer to start of linked list */
};


/* element of a linked list */
struct element {
	int count;
	char *word;
	struct element *next;
};


struct element *create_element(struct element *p, char *word)
{
	p = malloc(sizeof(struct element));

	p->word = malloc(strlen(word) + 1);	
	p->count = 1;
	p->next = NULL;

	strcpy(p->word, word);
	return p;
}


struct node *create_node(struct node *p, char *word)
{
	p = malloc(sizeof(struct node));
	
	p->lnode = p->rnode = NULL;	
	p->start_ll = create_element(p->start_ll, word);

	return p;
}


/* append: appends an element to the end of the linked list */
struct element *append(struct element *p, char *word)
{
	/* on the end of the list, extend it. */
	if (p == NULL) {
		p = create_element(p, word);
	
	/* word already on ll, increment counter */
	} else if (strcmp(p->word, word) == 0) {
		p->count += 1;

	/* you are not at the end of the ll and the word hasn't been seen yet, keep going */
	} else  {
		p->next = append(p->next, word);
	}

	/* if malloc where to return NULL in create_element, it would crash the program */
	/* as you are trying to dereference a NULL pointer */
	return p;
}


/* searchpos: searches the node in the binary tree the word belongs to */
struct node *searchpos(struct node *p, char *word, int n_letters)
{
	/* new node, create it */
	if (p == NULL)
		return create_node(p, word);

	/* compare the first word of the linked list this node
	 * points to and the word passed in to the function */
	int result = comp(p->start_ll->word, word, n_letters);

	/* belongs in the group, append it */
	if (result == BELONGS)
		p->start_ll = append(p->start_ll, word);

	/* doesn't belong in the group and the word passed in to the func is > */
	if (result == DIFFERS_GT)
		p->rnode = searchpos(p->rnode, word, n_letters);

	/* doesn't belong in the group and the word passed in to the func is < */
	if (result == DIFFERS_LT)
		p->lnode = searchpos(p->lnode, word, n_letters);

	return p;
}


/* swap: swaps two words between two pointers to element structures */
void swap(struct element *a, struct element *b)
{
	char *temp = a->word;
	a->word = b->word;
	b->word = temp;
}

/* qsort_ll: quicksort on a linked list. kinda sloppy tho lol */
/* uses the left argument as its pivot */
void qsort_ll(struct element *left, struct element *right)
{
	/* left can == NULL on the second call of 'qsort_ll(last->next, right)' */
	if (left == NULL || left == right)
		return;
	
	struct element *last = left;		/* last element you swapped */
	struct element *iter = left->next;	/* start iterating over left+1 */

	/* iterate over the section of the linked list that was given */
	while (iter != right->next) {
		if (strcmp(iter->word, left->word) < 0)
			swap(iter, last = last->next);
		iter = iter->next;
	}

	swap(left, last);
	qsort_ll(left, last);
	qsort_ll(last->next, right);
}


/* last: returns a pointer to the LAST element in a linked list */
struct element *last(struct element *p)
{
	while (p->next != NULL)
		p = p->next;
	return p;
}


/* pllist: print a linked list */
void pllist(struct element *p)
{
	while (p != NULL) {
		printf("%d.- %s\n", p->count, p->word);
		p = p->next;
	}
}


/* pbintree: recursively print a binary tree */
void pbintree(struct node *p, _Bool reverse)
{
	if (p != NULL) {
		pbintree((reverse) ? p->lnode: p->rnode, reverse);

		qsort_ll(p->start_ll, last(p->start_ll));	/* sort ll */
		pllist(p->start_ll);						/* print ll */
		putchar('\n');

		pbintree((reverse) ? p->rnode: p->lnode, reverse);
	}
}


int getargs(int argc, char *argv[], int *n, _Bool *r)
{
	int c;

	while (--argc && (*++argv)[0] == '-')
		while (c = *++*argv)
			switch (c) {

				case 'r':	/* reverse order */
					*r = 1;
					break;

				case 'n':	/* set first n of letters words must match */
					if (--argc < 1 || (*n = atoi(*++argv)) <= 0)
						goto error;
					/* terminate string you just read w/ atoi so you can break 2nd while loop */
					(*argv)[1] = '\0';					
					break;

				default:				
					goto error;
					break;
			}

	if (argc > 0)
		goto error;
	else
		return 0;

	error:
		printf("ERROR, usage: -rn NATURAL_NUMBER\n");
		return 1;
}


int main(int argc, char *argv[])
{
	struct node *root = NULL;
	char word[MAXWORD];
	
	int n_letters = DEFAULT;	/* first n letters that must be equal to belong in the same group */
	_Bool reverse = 0;			/* whether or not it should print in reverse order */

	if (getargs(argc, argv, &n_letters, &reverse))	/* returns 1 if error */
		return 1;

	while (get_word(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '_')
			root = searchpos(root, word, n_letters);

	pbintree(root, reverse);
}