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

static char	*str_append(char *stash, char *buf, size_t buf_len, size_t *total_len)
{
	size_t	old_len;
	char	*tmp;

	old_len = *total_len;
	tmp = malloc(old_len + buf_len + 1);
	if (!tmp)
	{
		free(stash);
		return (NULL);
	}
	if (stash)
		memcpy(tmp, stash, old_len);
	memcpy(tmp + old_len, buf, buf_len);
	tmp[old_len + buf_len] = '\0';
	free(stash);
	*total_len += buf_len;
	return (tmp);
}

static void	ft_filter(char *s, size_t slen, char *pattern, size_t patternlen)
{
	char	*end;
	char	*found;
	size_t	i;

	end = s + slen;
	while (s < end)
	{
		found = memmem(s, end - s, pattern, patternlen);
		if (!found)
		{
			write(1, s, end - s);
			return ;
		}
		if (found > s)
			write(1, s, found - s);
		i = 0;
		while (i++ < patternlen)
			write(1, "*", 1);
		s = found + patternlen;
	}
}

int	main(int argc, char **argv)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*stash;
	size_t		total_len;
	ssize_t		bytes_read;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	stash = NULL;
	total_len = 0;
	while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		stash = str_append(stash, buffer, bytes_read, &total_len);
		if (!stash)
		{
			perror("Error");
			return (1);
		}
	}
	if (bytes_read == -1)
	{
		perror("Error");
		free(stash);
		return (1);
	}
	if (!stash)
		return (0);
	ft_filter(stash, total_len, argv[1], strlen(argv[1]));
	free(stash);
	return (0);
}
