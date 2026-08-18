/*
 * Compact filter: read all stdin, overwrite matches with '*', write once.
 *
 * Compile: gcc -Wall -Wextra -Werror -D_GNU_SOURCE -D BUFFER_SIZE=42 -o filter filter_simple.c
 * Test:    echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
 *          ***defaaa***de******d***$
 */

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/*
 * s           = whole input buffer (never moved — needed for the final write)
 * slen        = its length
 * pattern     = string to hide (argv[1])
 * patternlen  = strlen(pattern)
 * pos         = where we search from (advances through s)
 *
 * memmem finds the next match. Remaining length is s_end - pos.
 *
 * On each hit: overwrite the match with '*'s, then jump past it
 * (non-overlapping, same as sed s/pattern/stars/g).
 * When memmem returns NULL, no more matches — write the whole buffer once.
 */
static void	filter(char *s, int slen, char *pattern, int patternlen)
{
	char	*pos;
	int		i;

	pos = s;
	while ((pos = memmem(pos, strlen(pos), pattern, (size_t)patternlen)))
	{
		i = 0;
		while (i < patternlen)		/* replace this match in place */
		{
			pos[i] = '*';
			i++;
		}
		pos += patternlen;		/* continue after the match */
	}
	write(1, s, (size_t)slen);
}

int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	char	*tmp = NULL;
	char	*result = NULL;
	int		total_read = 0;
	ssize_t	bytes_current;

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
