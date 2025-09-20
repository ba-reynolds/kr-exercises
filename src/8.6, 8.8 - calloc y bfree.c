#include <stddef.h>		// size_t, NULL
#include <stdio.h>

#define BUFFERSIZE 100000
void *sbrk(size_t nbytes)
{
	static char buffer[BUFFERSIZE];
	static char *bufferpos = buffer;

	bufferpos += nbytes;
	if (bufferpos > buffer + BUFFERSIZE)
		return NULL;

	return bufferpos - nbytes;
}


typedef struct header {
	size_t size;
	struct header *next;
} Header;


Header base = {0, NULL};
Header *freeptr = NULL;

Header *morecore(size_t);
void my_free(void *);


void *my_malloc(size_t nbytes)
{
	Header *iterptr;
	Header *prevptr;
	size_t nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	prevptr = freeptr;
	if (prevptr == NULL) {
		base.next = freeptr = prevptr = &base;
		base.size = 0;
	}

	for (iterptr = prevptr->next; ; prevptr = iterptr, iterptr = iterptr->next) {
		if (iterptr->size >= nunits) {
			if (iterptr->size == nunits) {
				prevptr->next = iterptr->next;
			}
			else {
				iterptr->size -= nunits;
				iterptr += iterptr->size;
				iterptr->size = nunits;
			}

			freeptr = prevptr;
			return iterptr+1;
		}
		else {
			iterptr = morecore(nunits);
			if (iterptr == NULL) {
				return NULL;
			}
		}
	}
}

#define MIN_NUNITS 1024
Header *morecore(size_t nunits)
{
	char *memoryblock;
	Header *blockheader;

	if (nunits < MIN_NUNITS)
		nunits = MIN_NUNITS;

	memoryblock = sbrk(nunits * sizeof(Header));
	if (memoryblock == (char *) -1)
		return NULL;

	blockheader = (Header *)memoryblock;
	blockheader->size = nunits;

	my_free(blockheader+1);
	return freeptr;
}


void my_free(void *block)
{
	Header *iterptr;
	Header *headptr;

	headptr = (Header *)block - 1;

	for (iterptr = freeptr; !(headptr > iterptr && headptr < iterptr->next); iterptr = iterptr->next)
		if (iterptr >= iterptr->next && (headptr > iterptr || headptr < iterptr->next))
			break;

	if (headptr + headptr->size == iterptr->next) {
		headptr->size += iterptr->next->size;
		headptr->next = iterptr->next->next;
	}
	else
		headptr->next = iterptr->next;

	if (iterptr + iterptr->size == headptr) {
		iterptr->size += headptr->size;
		iterptr->next = headptr->next;
	}
	else
		iterptr->next = headptr;

	freeptr = iterptr;
}


void *my_calloc(size_t nitems, size_t size)
{
	long nbytes = nitems * size;
	char *space = my_malloc(nbytes);
	while (--nbytes >= 0)
		space[nbytes] = 0;

	return (void *)space;
}


void bpfree(void *p, size_t n)
{
	Header *blockheader;
	blockheader = (Header *)p;

	blockheader->size = (n + sizeof(Header) - 1) / sizeof(Header) + 1;
	my_free(blockheader+1);
}



int main()
{
	static char block[SIZE];
	size_t size = SIZE;

	my_malloc(1);

	printf("%d %d\n", freeptr, &base);
	printf("size: %d\n", freeptr->size);
	printf("size: %d\n", freeptr->next->size);
	printf("size: %d\n", freeptr->next->next->size);

	bpfree(block, size);

	printf("%d %d\n", freeptr, &base);
	printf("size: %d\n", freeptr->size);
	printf("size: %d\n", freeptr->next->size);
	printf("size: %d\n", freeptr->next->next->size);
}