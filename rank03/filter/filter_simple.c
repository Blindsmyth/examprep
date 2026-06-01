/*
 * Easier-to-learn version of filter (for study only).
 * Same behavior as filter.c for the exam examples.
 *
 * Idea: walk the string with pointer `s` (like filter.c).
 *   1. Find next occurrence of pattern (memmem)
 *   2. Print everything from pos up to the match
 *   3. Print one '*' per character in the pattern
 *   4. Move s to just after the match and repeat
 *
 * Compile: gcc -D_GNU_SOURCE -g -o filter_simple filter_simple.c
 * Run:     ./filter_simple abc < test.txt
 */

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

static void	write_stars(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		write(1, "*", 1);
		i++;
	}
}

/*
 * Replace every non-overlapping occurrence of pattern in s[0..slen).
 * No sliding window — one clear loop.
 */
static void	ft_filter_simple(char *s, size_t slen, char *pattern, size_t patternlen)
{
	char	*pattern_start;
	char	*s_end;

	s_end = s + slen;
	while (s < s_end)
	{
		pattern_start = memmem(s, (size_t)(s_end - s), pattern, patternlen);
		if (!pattern_start)
		{
			write(1, s, (size_t)(s_end - s));
			return ;
		}
		write(1, s, (size_t)(pattern_start - s));
		write_stars(patternlen);
		s = pattern_start + patternlen;
	}
}

int	main(int argc, char **argv)
{
	char		buffer[BUFFER_SIZE];
	char		*temp;
	char		*result;
	int		total_read;
	ssize_t		bytes_current;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	temp = NULL;
	result = NULL;
	total_read = 0;
	while ((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, total_read + bytes_current + 1);
		if (!temp)
		{
			perror("Error");
			free(result);
			return (1);
		}
		result = temp;
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
		ft_filter_simple(result, (size_t)total_read, argv[1], strlen(argv[1]));
		free(result);
	}
	return (0);
}
