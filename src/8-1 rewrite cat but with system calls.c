#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define CANTOPENFILE 1
#define STDOUTERROR 2



void error(char *msg, ...)
{
	va_list args;
	va_start(args, msg);

	fprintf(stderr, "error: ");
	vfprintf(stderr, msg, args);
	fprintf(stderr, "\n");

	va_end(args);
	exit(1);
}



int showfile(char *filename)
{
	int fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		return CANTOPENFILE;
	
	char buf[BUFSIZ];
	int n;

	while ((n = read(fd, buf, sizeof buf)) > 0)	// read N chars from file
		if (write(1, buf, n) != n)				// write N chars to stdout
			return STDOUTERROR;

	return 0;
}


int getchar()
{
	static char buf[BUFSIZ];
	static char *bufp;
	static int n;

	if (n == 0) {
		n = read(0, buf, BUFSIZ);
		bufp = buf;
	}
		
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}


/* "Termination of a program via exit or return from the main program closes all open files."  */
int main(int argc, char *argv[])
{
	char *prog = argv[0];

	if (argc == 1) {
		int c;
		while ((c = getchar()) != EOF)
			if (putchar(c) == EOF)
				error("%s couldn't write to stdout", prog);
		return 0;
	}

	int errortype;
	while (*++argv)
		if (errortype = showfile(*argv))
			switch (errortype) {
				case CANTOPENFILE:
					error("%s couldn't open file %s", prog, *argv);
				case STDOUTERROR:
					error("%s couldn't write to stdout", prog);
			}
	return 0;
}

/* ------------------------------------------------------- */
