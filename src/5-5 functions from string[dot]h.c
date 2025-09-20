#include <stdio.h>

/* copy at most n characters of string ct to s; return s.
Pad with '\0''s if ct has fewer than n characters. */
char *strncpy(char *s, char *ct, int n)
{
	char *cs = s;		/* copy of s, could return s-n but n gets decreased in 'if' */
	while (*ct && n--)
		*s++ = *ct++;
	while (n-- >= 0)
		*s++ = '\0';
	*s = '\0';
	return cs;
}

/* concatenate at most n characters of string ct to string s,
terminate s with '\0'; return s. */
char *strncat(char *s, char *ct, int n)
{
	char *cs = s; /* copy of s */
	while (*s)
		s++; /* incrementing in the while will make you skip the null terminator */
	while (*ct && n--)
		*s++ = *ct++;
	*s = '\0';
	return cs;
}

/* compare at most n characters of string cs to string ct; 
return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct. */
int strcmp(char *cs, char *ct)
{
	for (; *cs == *ct; cs++, ct++)
		if (*cs == '\0')
			return 0;
	return *cs - *ct;
}

#define SIZE 100
int main()
{
	char str[SIZE];
	char *p = "Buenos dias";
	printf("%s\n", strncpy(str, p, 8));

	// char str[SIZE] = "Buenos dias 123 ";
	// char *p = "probando probando!";
	// printf("%s\n", strncat(str, p, 312));
	
	// char *str1 = "Buenos di";
	// char *str2 = "Buenos d";
	// int x = strcmp(str1, str2);
	// printf("%d", x);

}