#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline_(char *arr, int limit)
{
	char *start = arr;
	int c;
	while (--limit && (c = getchar()) != EOF && c != '\n')
		*arr++ = c;
	*arr = '\0';
	return arr-start;
}


int find(int argc, char *argv[])
{
	char line[MAXLINE];
	int except, enumerate, linenum;
	except = enumerate = linenum = 0;

	while (--argc && **++argv == '-')
		while (*++*argv)
			switch (**argv) {
			case 'x':
				except = 1;
				break;
			case 'n':
				enumerate = 1;
				break;
			default:
				argc = -1;
				break;
			}

	/* at this point only the pattern to look for should be left */
	if (argc != 1)
		printf("usage: find -x -n pattern\n");
	else
		while (getline_(line, MAXLINE) > 0) {
			++linenum;
			if ((strstr(line, *argv) != NULL) ^ except) {
				if (enumerate)
					printf("%d.- ", linenum);
				printf("%s\n", line);
			}
		}
}


int main(int argc, char *argv[])
{
	find(argc, argv);
}