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
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static void filter(char *s, int slen, char *pattern, int patternlen)
{
	char	*pattern_start;
	char	*s_end;
	int	i;
	
	s_end = s + slen;
	while (s < s_end)
	{
		pattern_start = memmem(s, (size_t(s_end - s)), pattern, size_t(pattern_start))
		if(!pattern_start
		{
			write(1, s, (size_t)(s_end - s));
			return;
		}
		write(1, s, (size_t)(pattern_start - s));
		i = 0;
		while(i < pattern_len)
		{
			write(1, "*", 1);
			i++;
		}
		s = pattern_start + patternlen;
	}
}

int	error(void)
{
	perror("ERROR");
	free (result);
	return (1);
}

int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	char	*tmp = NULL;
	char	*result NULL;
	ssize_t	bytes_current = 0;
	int	total_read = 0;
	
	if(argc !=2 || argv[1][0] == '\0')
		return (1);
	
	while((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		tmp = realloc(result, total_read + bytes_current + 1);
		if (!tmp)
			return(error(void));
			
		result = tmp;
		memmove(result + total_read, buffer, bytes_current);
		total_read += bytes_current;
	}
	if (bytes_current == -1)
	{
			return(error(void));
	}
	if (result)
	{
		result[total_read] = '\0';
		filter(result, total_read, argv[1], (int)strlen(argv[1]));
	}
	free(result);
	return(0);
}
