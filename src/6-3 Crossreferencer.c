#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "input.c"

#define MAX_WORD 100
#define NUM_NW sizeof(noise_words) / sizeof(*noise_words)

char *noise_words[] = {
	"and",
	"the"
};


struct node {
	char *word;

	struct line_ll *lines;
	struct node *lnode;
	struct node *rnode;
};


struct line_ll {
	int line_num;
	struct line_ll *next;
};


struct line_ll *lalloc(int line_num)
{
	struct line_ll *space = malloc(sizeof(struct line_ll));
	space->line_num = line_num;
	space->next = NULL;

	return space;
}


struct node *nalloc(char word[], int line_num)
{
	struct node *space = malloc(sizeof(struct node));
	space->word = malloc(strlen(word)+1);
	strcpy(space->word, word);

	space->lines = lalloc(line_num);
	space->rnode = space->lnode = NULL;

	return space;
}


void find_line(struct line_ll *start, int line_num)
{
	/* a match... there's no need to have the same number in the list */
	if (start->line_num == line_num)
		return;

	if (start->next == NULL)				/* extend the list */
		start->next = lalloc(line_num);
	else									/* keep searching */
		find_line(start->next, line_num);
}


struct node *find_word(struct node *root, char word[], int line_num)
{
	if (root == NULL)
		return nalloc(word, line_num);

	int cond = strcmp(word, root->word);

	if (cond == 0)
		find_line(root->lines, line_num);
	else if (cond < 0)
		root->lnode = find_word(root->lnode, word, line_num);
	else
		root->rnode = find_word(root->rnode, word, line_num);

	return root;
}


void show_line_nums(struct line_ll *start)
{
	while (start != NULL) {
		printf("%5d", start->line_num);
		start = start->next;
	}
	putchar('\n');
}


void show_bintree(struct node *root)
{
	if (root == NULL)
		return;

	show_bintree(root->lnode);

	printf("%20s - ", root->word);
	show_line_nums(root->lines);

	show_bintree(root->rnode);
}


/* case insensitive string comparison */
int dull_strcmp(char *a, char *b)
{
	for (; tolower(*a) == tolower(*b); a++, b++)
		if (*a == '\0')
			return 0;
	return *a - *b;
}


int is_noise_word(char word[])
{
	for (int i = 0; i < NUM_NW; i++)
		if (dull_strcmp(word, noise_words[i]) == 0)
			return 1;
	return 0;
}


int main()
{
	char word[MAX_WORD] = {};
	struct node *root = NULL;	/* root of the binary tree */
	int line_number = 1;		/* current line number of the word you are reading */
	int add;					/* to increment line_number */

	while (word[0] != EOF) {

		add = get_word(word, MAX_WORD);
		if (isalpha(word[0]) && !is_noise_word(word))
			root = find_word(root, word, line_number);
		line_number += add;	
		/* 
			line_number gets incremented here and not on top of the loop
			because if a word is at the end of the line then it will get the wrong line number
		*/
	}
	show_bintree(root);
}
