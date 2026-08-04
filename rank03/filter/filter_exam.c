/*
 * Exam-ready filter (42_examshell rank03 level1 / filter subject).
 *
 * Compile: gcc -Wall -Wextra -Werror -D_GNU_SOURCE -D BUFFER_SIZE=42 -o filter filter_exam.c
 * Test:    echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
 */

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static void	filter(char *s, int slen, char *pattern, int patternlen)
{
	char	*pattern_start;
	char	*s_end;
	int		i;

	s_end = s + slen;
	while (s < s_end)
	{
		pattern_start = memmem(s, (size_t)(s_end - s), pattern, (size_t)patternlen);
		if (!pattern_start)
		{
			write(1, s, (size_t)(s_end - s));
			return ;
		}
		write(1, s, (size_t)(pattern_start - s));
		i = 0;
		while (i < patternlen)
		{
			write(1, "*", 1);
			i++;
		}
		s = pattern_start + patternlen;
	}
}

int	main(int argc, char **argv)
{
	char		buffer[BUFFER_SIZE];
	char		*tmp = NULL;
	char		*result = NULL;
	ssize_t		bytes_current = 0;
	int		total_read = 0;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	while ((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		tmp = realloc(result, total_read + bytes_current + 1);
		if (!tmp)
		{
			perror("Error");
			free(result);
			return (1);
		}
		result = tmp;
		memmove(result + total_read, buffer, bytes_current);
		total_read += bytes_current;
	}
	if (bytes_current == -1)
	{
		perror("Error");
		free(result);
		return (1);
	}
	if (result)
	{
		result[total_read] = '\0';
		filter(result, total_read, argv[1], (int)strlen(argv[1]));
	}
	free(result);
	return (0);
}
