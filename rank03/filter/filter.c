/*
Assignment name:filter
files to turn in: filter.c
Allowed functions and globals: read, write, strlen, memmem, memmove, malloc, calloc, 
realloc, free, printf, fprintf,stdout, stderr, perror
Write a program that will take one and only one argument s

Your programm will then read from stdin and write all the content read in stdout, except that 
every occurence of s must be replaced by '*' (as many as the length of s) 
Your prgogramm will be tested with random buffer sizes using a custom read function. Therefore
the buffer being set in your programm will be filled with a different number of chars each call.

./filter hello
will behave the same way as
sed 's/hello/ *****g'

./filter abc
will behave the same way as
sed 's/hello/xxx/g'

More generally your pgrogramm must be equivalent of the shell script filter.sh presultent in this directory.
You can compare your programm with it.

In case of error during a read or a malloc you must write "Error" followed by the error message in stderr
and return 1. If the programm is called without arguments or an empty argument or with multiple arguments
it must return 1

For example this should work:
echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -c
***defaaa***de******d***

echo 'ababcabababc' | ./filter abab | -e
*****ab*****
*/
#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

void	ft_filter (char *s, size_t slen, char *pattern, size_t patternlen)
{
	char	*pattern_start;
	char *pattern_end;
	char *s_end = s + slen;

	pattern_start = memmem(s, slen, pattern, patternlen);
	pattern_end = pattern_start + patternlen;

	while (*s)
	{
		if (!pattern_start)
		{
			write(1, s, 1);
			s++;
		}
		if (s < pattern_start)
		{
			write(1, s, 1);
			s++;
		}
		else if (s < pattern_end)
		{
			write(1,"*",1);
			s++;
			pattern_start++;
		}
		else if (s == pattern_end)
		{
			pattern_start = memmem (s, s_end - s, pattern, patternlen);
			pattern_end = pattern_start + patternlen;
			s++;
		}
	}
}

int	main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE];
	char *temp = NULL;
	char *result = NULL;
	int	total_read = 0;
	ssize_t bytes_current;

	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	while ((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, bytes_current + total_read + 1);
		if (!temp)
		{
			perror("realloc");
			free(result);
			return 1;
		}
		result = temp;
		total_read += bytes_current;
	}
	memmove(result + bytes_current, buffer, BUFFER_SIZE);
	result[total_read] = '\0';

	ft_filter(result, total_read, argv[1], strlen(argv[1]));
	return 0;
}